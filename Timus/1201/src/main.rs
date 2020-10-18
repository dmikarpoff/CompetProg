use std::io;

fn is_leap(y: u32) -> bool {
    y % 4 == 0 && (y % 100 != 0 || y % 400 == 0)
}

fn main() {
    let mut buffer = String::new();
    io::stdin().read_line(&mut buffer).unwrap();
    let input_vec: Vec<u32> = 
        buffer.trim().split(' ').map(|x| x.parse::<u32>().unwrap()).collect();
    let d = input_vec[0];
    let m = input_vec[1];
    let y = input_vec[2];

    let mut week_day = 5;
    for cur_y in 1600..y {
        week_day += if is_leap(cur_y) { 366 % 7 } else { 365 % 7 };
        week_day = week_day % 7;
    }
    let month_len = vec!(31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31);
    for cur_m in 1..m {
        week_day += month_len[(cur_m - 1) as usize];
        if cur_m == 2 && is_leap(y) {
            week_day += 1;
        }
        week_day = week_day % 7;
    }
    let cur_month_len = month_len[(m - 1) as usize] + 
                            if m == 2 && is_leap(y) { 1 } else { 0 };
    let week_num = (week_day + cur_month_len) / 7 + 
                if (week_day + cur_month_len) % 7 != 0 { 1 } else { 0 };

    for i in 0..7 {
        let mut output = String::new();
        output += match i {
            0 => "mon",
            1 => "tue",
            2 => "wed",
            3 => "thu",
            4 => "fri",
            5 => "sat",
            6 => "sun",
            _ => panic!("Impossible value")
        };
        let mut cur_day = -(week_day as i32) + i + 1;
        for _ in 0..week_num {
            if cur_day > 0 && cur_day <= cur_month_len {
                if cur_day == (d as i32) {
                    output = format!("{} [{: >2}]", output, cur_day);
                } else {
                    if cur_day + 7 <= cur_month_len {
                        output = format!("{}  {: >2} ",output, cur_day);
                    } else {
                        output = format!("{}  {: >2}",output, cur_day);
                    }
                };
                // output += ".";
            } else {
                if cur_day <= 0 {
                    output += "     ";
                }
            }
            cur_day += 7;
        }

        println!("{}", output);
    }
}
