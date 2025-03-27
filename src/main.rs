use std::env;
use std::process;

mod odj_loader;

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() != 2 {
        process::exit(1)
    }

    let file_path = &args[1];

    println!("Opening file : {file_path}");
}
