use std::io;
use std::io::prelude::*;

fn main() {
    let mut buffer = String::new();
    io::stdin().read_line(&mut buffer).unwrap();
    let n: usize = buffer.trim().parse().unwrap();
    let mut v: Vec<(i32, i32)> = Vec::new();
    let stdin = io::stdin();
    for ln in stdin.lock().lines() {
        let line = ln.unwrap();
        let p = line.split(' ').collect::<Vec<_>>();
        let x: i32 = p[0].parse().unwrap();
        let y: i32 = p[1].parse().unwrap();
        v.push((x, y));
    }
    let mut s: i64 = 0;
    for i in 0..n {
        let j: usize = (i + 1) % n;
        s += ((v[j].0 - v[i].0) * (v[i].1 + v[j].1)) as i64;
    }
    println!("{}", if s > 0 {"cw"} else {"ccw"});
}