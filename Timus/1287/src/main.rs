use std::io;
use std::io::prelude::*;
use std::cmp;

fn main() {
    let mut buffer = String::new();
    io::stdin().read_line(&mut buffer).expect("Read line with number");
    let n: usize = buffer.trim().parse().expect("Integer value");
    let mut field: Vec<String> = Vec::with_capacity(n);
    for t in io::stdin().lock().lines() {
        field.push(t.unwrap());
    }

    let mut max_len_s: usize = 0;
    let mut max_len_capital_s: usize = 0;

    let mut row_last = vec!['?'; n];
    let mut row_len = vec![0; n];
    let mut col_last = vec!['?'; n];
    let mut col_len = vec![0; n];
    let mut diag_last = vec!['?'; 2 * n - 1];
    let mut diag_len = vec![0; 2 * n - 1];
    let mut anti_last = vec!['?'; 2 * n - 1];
    let mut anti_len = vec![0; 2 * n - 1];

    for i in 0usize..n {
        for (j, symb) in field[i].trim().chars().enumerate() {
            if symb == row_last[i] {
                row_len[i] += 1;
            } else {
                row_len[i] = 1;
                row_last[i] = symb;
            }
            if symb == col_last[j] {
                col_len[j] += 1;
            } else {
                col_len[j] = 1;
                col_last[j] = symb;
            }
            if symb == diag_last[i + j] {
                diag_len[i + j] += 1;
            } else {
                diag_len[i + j] = 1;
                diag_last[i + j] = symb;
            }
            let sub = n + i - j - 1;
            if symb == anti_last[sub] {
                anti_len[sub] += 1;
            } else {
                anti_len[sub] = 1;
                anti_last[sub] = symb;
            }

            if row_last[i] == 's' {
                max_len_s = cmp::max(row_len[i], max_len_s);
            }
            if row_last[i] == 'S' {
                max_len_capital_s = cmp::max(row_len[i], max_len_capital_s);
            }
            if col_last[j] == 's' {
                max_len_s = cmp::max(col_len[j], max_len_s);
            }
            if col_last[j] == 'S' {
                max_len_capital_s = cmp::max(col_len[j], max_len_capital_s)
            }
            if diag_last[i + j] == 's' {
                max_len_s = cmp::max(diag_len[i + j], max_len_s);
            }
            if diag_last[i + j] == 'S' {
                max_len_capital_s = cmp::max(diag_len[i + j], max_len_capital_s)
            }
            if anti_last[sub] == 's' {
                max_len_s = cmp::max(anti_len[sub], max_len_s);
            }
            if anti_last[sub] == 'S' {
                max_len_capital_s = cmp::max(anti_len[sub], max_len_capital_s)
            }
        }
    }

    println!("{}", if max_len_capital_s > max_len_s {'S'} else if max_len_s > max_len_capital_s {'s'} else {'?'});
    println!("{}", cmp::max(max_len_s, max_len_capital_s));
}
