struct Point {
    x: f64,
    y: f64
}

fn dist(a: &Point, b: &Point) -> f64 {
    (a.x - b.x).hypot(a.y - b.y)
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_line(&mut buf).expect("Line with vertex nums");
    let n = buf.trim().parse::<usize>().unwrap();
    let mut pts = vec!();
    for _ in 0..n {
        let mut buf = String::new();
        std::io::stdin().read_line(&mut buf).expect("Vertex expected");
        let v = buf.trim().split(" ")
                    .map(|x| x.parse::<f64>().unwrap())
                    .collect::<Vec<_>>();
        pts.push(Point {
            x: v[0],
            y: v[1]
        });
    }

    if n == 1 {
        println!("0.000");
        return;
    }

    let mut min_dist = 1E+100;
    let mut tbl_dist = vec![vec![0.0; n]; n];
    for i in 0..n {
        for j in 0..n {
            tbl_dist[i][j] = dist(&pts[i], &pts[j]);
        }
    }

    let mut dp_upper = vec![vec![1E+100; n]; n];
    let mut dp_lower = vec![vec![1E+100; n]; n];
    for i in 0..n {
        dp_lower[i][i] = 0.0;
        dp_upper[i][i] = 0.0;
        for j in 0..n {
            let l = (i + j) % n;
            let mut r = if l == i {(i + n - 1) % n} else {i};
            loop {
                if r != i {
                    dp_lower[l][r] = 1E+100;
                    let prev_r: usize = (r + 1) % n;
                    let est_d = dp_lower[l][prev_r] + tbl_dist[prev_r][r];
                    if est_d < dp_lower[l][r] {
                        dp_lower[l][r] = est_d;
                    }
                    let est_d = dp_upper[l][prev_r] + tbl_dist[l][r];
                    if est_d < dp_lower[l][r] {
                        dp_lower[l][r] = est_d;
                    }
                }
                if l != i {
                    let prev_l: usize = (l + n - 1) % n;
                    dp_upper[l][r] = 1E+100;
                    let est_d = dp_upper[prev_l][r] + tbl_dist[prev_l][l];
                    if est_d < dp_upper[l][r] {
                        dp_upper[l][r] = est_d;
                    }
                    let est_d = dp_lower[prev_l][r] + tbl_dist[l][r];
                    if est_d < dp_upper[l][r] {
                        dp_upper[l][r] = est_d;
                    }
                }

                if l == r {
                    if l != i {
                        if dp_lower[l][r] < min_dist {
                            min_dist = dp_lower[l][r];
                        }
                        if dp_upper[l][r] < min_dist {
                            min_dist = dp_upper[l][r];
                        }
                    }
                    break;
                }
                r = (r + n - 1) % n;
            }
        }
        
    }
    println!("{:.3}", min_dist);
}
