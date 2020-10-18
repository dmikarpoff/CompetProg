use std::io;
use std::collections::VecDeque;
use std::collections::HashSet;
use std::collections::HashMap;
use std::fmt;

#[derive(Copy, Clone, PartialEq)]
enum TokenType {
    Not,
    And,
    Or,
    True,
    False,
    LeftParen,
    RightParen,
    Var
}

enum NonTerminal {
    A,
    M,
    N,
    Terminal
}

enum Direction {
    Left, 
    Right,
    Up,
    Down
}

#[derive(Clone)]
struct Token {
    pub token_type: TokenType,
    pub text: String
}

impl fmt::Display for Token {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.text)
    }
}

struct AstNode {
    pub token: Option<Token>,
    pub node_type: NonTerminal,
    pub children: Vec<AstNode>
}

fn string_to_token(str: &String) -> TokenType {
    match str.as_str() {
        "NOT" => TokenType::Not,
        "AND" => TokenType::And,
        "OR" => TokenType::Or,
        "TRUE" => TokenType::True,
        "FALSE" => TokenType::False,
        "(" => TokenType::LeftParen,
        ")" => TokenType::RightParen,
        _ => TokenType::Var
    }
}

fn transition_n(state: i32) -> i32 {
    match state {
        0 | 7 => 3,
        4 => 9,
        6 | 15 | 19 => 12,
        8 => 17,
        13 => 21,
        20 => 24,
        _ => panic!("Unexpected state {} after reduction", state)
    }
}

fn estimate(node: &AstNode, register: &HashMap<String, bool>) -> bool {
    match &node.token {
        &Some(ref token) => {
            match token.token_type {
                TokenType::True => true,
                TokenType::False => false,
                TokenType::Var => *register.get(&token.text).unwrap_or(&false),
                _ => panic!("Can't estimate value for token {}", &token.text)
            }
        }
        &None => {
            match node.node_type {
                NonTerminal::A => {
                    if node.children.len() == 3 {
                        let left = estimate(&node.children[0], &register);
                        let right = estimate(&node.children[2], &register);
                        left || right
                    } else {
                        let m = estimate(&node.children[0], &register);
                        m
                    }
                }
                NonTerminal::M => {
                    if node.children.len() == 3 {
                        let left = estimate(&node.children[0], &register);
                        let right = estimate(&node.children[2], &register);
                        left && right
                    } else {
                        let n = estimate(&node.children[0], &register);
                        n
                    }
                }
                NonTerminal::N => {
                    if node.children.len() == 2 {
                        !estimate(&node.children[1], &register)
                    } else if node.children.len() == 3 {
                        estimate(&node.children[1], &register)
                    } else {
                        estimate(&node.children[0], &register)
                    }
                }
                _ => panic!("Terminal nodes must be already handled")
            }
        }
    }
}

fn extract_token(q: &VecDeque<Token>) -> Option<Token> {
    match q.front() {
        Some(x) => Some(x.clone()),
        None => None
    }
}

fn main() {
    let mut expression = String::new();
    io::stdin().read_line(&mut expression).unwrap();

    let mut token_str = String::new();
    let mut token_queue: VecDeque<Token> = VecDeque::new();
    for c in expression.chars() {
        if c.is_alphabetic() && 
                (token_str.is_empty() || 
                 token_str.chars().last().unwrap().is_alphabetic()) {
            token_str.push(c);
            continue;
        }
        if !token_str.is_empty() {
            let node_type =  string_to_token(&token_str);
            token_queue.push_back(Token{token_type: node_type, text: token_str});
            token_str = String::new();
        }
        if !c.is_whitespace() {
            token_str.push(c);
            continue;
        }
    }
    
    let mut nodes: Vec<AstNode> = Vec::new();
    let mut state_stack: Vec<i32> = Vec::new();
    let mut state = 0;
    state_stack.push(0);

    loop {
        let cur_token = extract_token(&token_queue);
        match state {
            0 | 4 | 7 | 8 => {
                let cur_token = cur_token.unwrap();
                state = match cur_token.token_type {
                    TokenType::LeftParen => 6,
                    TokenType::True | TokenType::False | TokenType::Var => 5,
                    TokenType::Not => 4,
                    _ => panic!("Unexpected token in state 4")
                };
                state_stack.push(state);
                nodes.push(AstNode{token: Some(cur_token.clone()), node_type: NonTerminal::Terminal,
                                    children: vec!()});
                token_queue.pop_front();
            }
            1 => {
                state = match cur_token {
                    None => break,
                    Some(_) => 7
                };
                state_stack.push(state);
                nodes.push(AstNode{token: Some(cur_token.unwrap().clone()), node_type: NonTerminal::Terminal,
                                    children: vec!()});
                token_queue.pop_front();
            }
            2 => {
                let shift = match &cur_token {
                    &None => false,
                    &Some(ref token) => (token.token_type == TokenType::And)
                };
                if shift {
                    state = 8;
                    state_stack.push(state);
                    nodes.push(AstNode{token: Some(cur_token.unwrap().clone()), node_type: NonTerminal::Terminal,
                                        children: vec!()});
                    token_queue.pop_front();
                } else {
                    state_stack.pop();
                    let last_state = *state_stack.last().unwrap();
                    state = match last_state {
                        0 => 1,
                        6 => 10,
                        15 => 22,
                        _ => panic!("Unexpected state {} after reduction", last_state)
                    };
                    state_stack.push(state);
                    let var = nodes.pop().unwrap();
                    nodes.push(AstNode{token: None, node_type: NonTerminal::A,
                                        children: vec!(var)});                    
                }
            }
            3 | 12 => {
                state_stack.pop();
                let last_state = *state_stack.last().unwrap();
                state = match last_state {
                    0 => 2,
                    6 | 15 => 11,
                    7 => 16,
                    19 => 23,
                    _ => panic!("Unexpected state {} after reduction", last_state)
                };
                state_stack.push(state);
                let var = nodes.pop().unwrap();
                nodes.push(AstNode{token: None, node_type: NonTerminal::M,
                                    children: vec!(var)});
            }
            5 | 14 => {
                state_stack.pop();
                let last_state = *state_stack.last().unwrap();
                state = transition_n(last_state);
                state_stack.push(state);
                let var = nodes.pop().unwrap();
                nodes.push(AstNode{token: None, node_type: NonTerminal::N,
                                    children: vec!(var)});
            }
            6 | 13 | 15 | 19 | 20 => {
                let cur_token = cur_token.unwrap();
                state = match cur_token.token_type {
                    TokenType::LeftParen => 15,
                    TokenType::True | TokenType::False | TokenType::Var => 14,
                    TokenType::Not => 13,
                    _ => panic!("Unexpected token in state 4")
                };
                state_stack.push(state);
                nodes.push(AstNode{token: Some(cur_token.clone()), node_type: NonTerminal::Terminal,
                                    children: vec!()});
                token_queue.pop_front();
            }
            9 | 21 => {
                state_stack.pop();
                state_stack.pop();
                let last_state = *state_stack.last().unwrap();
                state = transition_n(last_state);
                state_stack.push(state);
                let n = nodes.pop().unwrap();
                let not = nodes.pop().unwrap();
                nodes.push(AstNode{token: None, node_type: NonTerminal::N,
                                    children: vec!(not, n)});
            }
            10 => {
                let cur_token = cur_token.unwrap();
                state = match cur_token.token_type {
                    TokenType::Or => 19,
                    TokenType::RightParen => 18,
                    _ => panic!("Unexpected token in state 4")
                };
                state_stack.push(state);
                nodes.push(AstNode{token: Some(cur_token.clone()), node_type: NonTerminal::Terminal,
                                    children: vec!()});
                token_queue.pop_front();
            }
            11 => {
                let shift = match &cur_token {
                    &None => false,
                    &Some(ref token) => (token.token_type == TokenType::And)
                };
                if shift {
                    state = 20;
                    state_stack.push(state);
                    nodes.push(AstNode{token: Some(cur_token.unwrap().clone()), node_type: NonTerminal::Terminal,
                                        children: vec!()});
                    token_queue.pop_front();
                } else {
                    state_stack.pop();
                    let last_state = *state_stack.last().unwrap();
                    state = match last_state {
                        0 => 1,
                        6 => 10,
                        15 => 22,
                        _ => panic!("Unexpected state {} after reduction", last_state)
                    };
                    state_stack.push(state);
                    let var = nodes.pop().unwrap();
                    nodes.push(AstNode{token: None, node_type: NonTerminal::A,
                                        children: vec!(var)});                    
                }
            }
            16 => {
                let shift = match &cur_token {
                    &None => false,
                    &Some(ref token) => (token.token_type == TokenType::And)
                };
                if shift {
                    state = 8;
                    state_stack.push(state);
                    nodes.push(AstNode{token: Some(cur_token.unwrap().clone()), node_type: NonTerminal::Terminal,
                                        children: vec!()});
                    token_queue.pop_front();
                } else {
                    state_stack.pop();
                    state_stack.pop();
                    state_stack.pop();
                    let last_state = *state_stack.last().unwrap();
                    state = match last_state {
                        0 => 1,
                        6 => 10,
                        15 => 22,
                        _ => panic!("Unexpected state {} after reduction", last_state)
                    };
                    state_stack.push(state);
                    let m = nodes.pop().unwrap();
                    let or = nodes.pop().unwrap();
                    let a = nodes.pop().unwrap();
                    nodes.push(AstNode{token: None, node_type: NonTerminal::A,
                                        children: vec!(a, or, m)});                    
                }        
            }
            17 | 24 => {
                state_stack.pop();
                state_stack.pop();
                state_stack.pop();
                let last_state = *state_stack.last().unwrap();
                state = match last_state {
                    0 => 2,
                    6 | 15 => 11,
                    7 => 16,
                    19 => 23,
                    _ => panic!("Unexpected state {} after reduction", last_state)
                };
                state_stack.push(state);
                let n = nodes.pop().unwrap();
                let and = nodes.pop().unwrap();
                let m = nodes.pop().unwrap();
                nodes.push(AstNode{token: None, node_type: NonTerminal::M,
                                    children: vec!(m, and, n)});
            }
            18 | 25 => {
                state_stack.pop();
                state_stack.pop();
                state_stack.pop();
                let last_state = *state_stack.last().unwrap();
                state = transition_n(last_state);
                state_stack.push(state);
                let rp = nodes.pop().unwrap();
                let a = nodes.pop().unwrap();
                let lp = nodes.pop().unwrap();
                nodes.push(AstNode{token: None, node_type: NonTerminal::N,
                                    children: vec!(lp, a, rp)});
            }
            22 => {
                let cur_token = cur_token.unwrap();
                state = match cur_token.token_type {
                    TokenType::Or => 19,
                    TokenType::RightParen => 25,
                    _ => panic!("Unexpected token in state 4")
                };
                state_stack.push(state);
                nodes.push(AstNode{token: Some(cur_token.clone()), node_type: NonTerminal::Terminal,
                                    children: vec!()});
                token_queue.pop_front();
            }
            23 => {
                let shift = match &cur_token {
                    &None => false,
                    &Some(ref token) => (token.token_type == TokenType::And)
                };
                if shift {
                    state = 20;
                    state_stack.push(state);
                    nodes.push(AstNode{token: Some(cur_token.unwrap().clone()), node_type: NonTerminal::Terminal,
                                        children: vec!()});
                    token_queue.pop_front();
                } else {
                    state_stack.pop();
                    state_stack.pop();
                    state_stack.pop();
                    let last_state = *state_stack.last().unwrap();
                    state = match last_state {
                        0 => 1,
                        6 => 10,
                        15 => 22,
                        _ => panic!("Unexpected state {} after reduction", last_state)
                    };
                    state_stack.push(state);
                    let m = nodes.pop().unwrap();
                    let or = nodes.pop().unwrap();
                    let a = nodes.pop().unwrap();
                    nodes.push(AstNode{token: None, node_type: NonTerminal::A,
                                        children: vec!(a, or, m)});                    
                }       
            }
            _ => panic!("Unexpected state of parser {}", state)
        }
    }
    
    assert_eq!(nodes.len(), 1);
    let root = nodes.pop().unwrap();

    let mut buffer = String::new();
    io::stdin().read_line(&mut buffer).unwrap();
    let temp_v : Vec<i32> = buffer.trim().split(' ').map(|x| x.parse::<i32>().unwrap()).collect();
    let n = temp_v[0];
    let m = temp_v[1];
    let k = temp_v[2];
    let mut crossing: HashSet<(i32, i32)> = HashSet::new();
    for _ in 0..m {
        let mut buffer = String::new();
        io::stdin().read_line(&mut buffer).unwrap();
        let temp = buffer.trim().split(' ').map(|x| x.parse::<i32>().unwrap()).collect::<Vec<i32>>();
        crossing.insert((temp[0], temp[1]));
    }
    let mut inv_points: HashMap<(i32, i32), String> = HashMap::new();
    for _ in 0..k {
        let mut buffer = String::new();
        io::stdin().read_line(&mut buffer).unwrap();
        let temp = buffer.trim().split(' ').collect::<Vec<&str>>();
        let x = temp[0].parse::<i32>().unwrap();
        let y = temp[1].parse::<i32>().unwrap();
        let reg = temp[2];
        inv_points.insert((x, y), String::from(reg));
    }
    let mut register: HashMap<String, bool> = HashMap::new();    
    let mut x = 0;
    let mut y = 0;
    let mut direction = Direction::Right;
    while x <= n && x >= -n && y <= n && y >= -n {
        println!("{} {}", x, y);
        match direction {
            Direction::Left => {x -= 1;},
            Direction::Right => {x += 1;},
            Direction::Up => {y += 1;},
            Direction::Down => {y -= 1; }
        }
        if crossing.contains(&(x, y)) {
            let right = estimate(&root, &register);
            direction = match direction {
                Direction::Left => if right { Direction::Up } else { Direction::Down },
                Direction::Right => if right { Direction::Down } else { Direction::Up },
                Direction::Up => if right { Direction::Right } else { Direction::Left },
                Direction::Down => if right { Direction::Left} else { Direction::Right}
            };
        }
        match inv_points.get(&(x, y)) {
            Some(var) => {
                let val = ! *register.get(var).unwrap_or(&false);
                *register.entry(var.clone()).or_insert(false) = val;
            }
            None => {}
        }
        
    }
}
