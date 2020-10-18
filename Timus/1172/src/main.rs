use std::io;

fn main() {
    let mut buffer = String::new();
    io::stdin().read_line(&mut buffer).unwrap();
    let n = buffer.trim().parse::<u64>().unwrap() as usize;
    let mut dp = vec![vec![vec![vec![0; 3];n + 1];n + 1];n + 1];
    println!("{}", dp[n - 1][n][n][0] / 2);
}
