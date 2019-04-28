#![allow(unused_imports)]
#![allow(unused_macros)]
use std::{
    io::{ self, Read, BufRead },
    collections::{
        HashMap,
        HashSet,
        BTreeMap,
        BTreeSet
    },
    cmp::{ min, max }
};

// Initialize the io. Single allocation, single read
macro_rules! init_io {
    ($next_line:ident) => {
        let mut input = String::new();
        io::stdin().read_to_string(&mut input).unwrap();
        #[allow(unused_variables, unused_mut)]
        let mut lines = input.lines();

        #[allow(unused_variables, unused_mut)]
        let mut $next_line = || {
            lines.next().unwrap()
        };
    };
}

// Parse each word in string, zero copy
macro_rules! parse_line {
    ($io:ident, ( $($type:tt),+ )) => {{
        let line = $io();
        parse_words!(line.split_whitespace(), ( $($type),+ ))
    }};
    ($io:ident, [ $type:tt ]) => {{
        let line = $io();
        parse_words!(line.split_whitespace(), [ $type ])
    }};
    ($io:ident, $type:tt) => {{
        let line = $io();
        parse_words!(line, $type)
    }};
}

/// Parse every word in iterator, zero copy.
/// Specify io and format. Formats:
/// - Parse each word as value in tuple: `(type0, type1, type2, ...)`
/// - Parse each word as value in vector: `[type]`
/// - Parse single word as type: `type`
/// `type` may be any type which implements `FromStr`, or `str`.
/// If `type` is `str` the word will be treated as a string slice.
macro_rules! parse_words {
    ($words:expr, ($($type:tt),+) ) => {{
        let mut words = $words;
        ( $( parse_words!(words.next().unwrap(), $type) ),+ )
    }};
    // Parse until not possible
    ($words:expr, [ $type:tt ] ) => {{
        let mut words = $words;
        let mut result = Vec::new();
        while let Some(Ok(value)) = words.next().map(|word| word.parse::<$type>()) {
            result.push(value);
        }
        result
    }};
    // Return word
    ($word:expr, str) => {{ $word }};
    // Return parsed type
    ($word:expr, $type:ty) => {{ $word.parse::<$type>().unwrap() }};
}


fn gcd(a: i32, b: i32) -> i32 {
    if a == 0 {
        b 
    } else {
        gcd(b % a, a)
    }
}

fn main() {
    init_io!(io);

    let n = parse_line!(io, usize);

    if n == 1 {
        println!("{}", 1);
        return;
    }
    
    let mut points = Vec::new();
    for _ in 0..n {
        let (x, y) = parse_line!(io, (i32, i32));
        points.push((x, y));
    }

    // HashMaps, för det är enkelt
    let mut strike = HashMap::new();
    let mut normal = HashMap::new();
    let mut striked = HashSet::new();

    strike.reserve(n*n);
    normal.reserve(n*n);
    striked.reserve(n);

    for i in 0..n {
        let (ax, ay) = points[i];
        striked.clear();

        for j in i+1..n {
            let (bx, by) = points[j];

            // Ingen mening att återuppfinna hjulet när någon annan har gjort ett bra jobb.
            // Källa: David Avellan-Hultman
            
            // Linjen som går genom (xi, yi) och (xj, yj) har ekvationen
            //     (xj - xi)(y - yi) = (yj - yi)(x - xi)
            //     (xj - xi)y + (yi - yj)x + (xi * yj - xj * yi) = 0
            //     ---yc----    ---xc----    --------cc---------
            // Koefficienterna delat med deras sgd identifierar linjen unikt
            let yc = bx - ax;
            let xc = ay - by;
            let cc = ax * by - bx * ay;

            // sgd(a, b, c) == sgd(a, sgd(b, c))
            // Koefficienter kan vara negativa
            // Standardisera så att första icke-noll koefficient är positiv
            let mut div = gcd(yc.abs(), gcd(xc.abs(), cc.abs()));
            if yc < 0 || (yc == 0 && (xc < 0 || (xc == 0 && cc < 0))) { div *= -1 };

            // div == 0 omm yc == xc == cc == 0
            // Detta inträffar bara om pi == pj, vilket är garanterat att inte hända
            // Alltså kan vi dividera
            let yc = yc / div;
            let xc = xc / div;
            let cc = cc / div;

            // Spara linjen om denna punkt inte redan ligger på den
            let line = (yc, xc, cc);
            if !striked.contains(&line) {
                striked.insert(line.clone());
                *strike.entry(line).or_insert(1) += 1;
            }

            // Nu till mittpunktsnormalen
            // Lutningen är -(xj - xi)/(yj - yi)
            // Den går genom ((xi + xj) / 2, (yi + yj) / 2)
            //     (yj - yi)(y - (yi + yj) / 2) = -(xj - xi)(x - (xi + xj) / 2)
            //     (yj - yi)(2y - yi - yj) + (xj - xi)(2x - xi - xj) = 0
            //     2(yj - yi)y + 2(xj - xi)x + yi^2 - yj^2 + xi^2 - xj^2 = 0
            // Uppprepa processen med koefficienterna
            let yc = 2 * (by - ay);
            let xc = 2 * (bx - ax);
            let cc = ay * ay - by * by + ax * ax - bx * bx;

            let mut div = gcd(yc.abs(), gcd(xc.abs(), cc.abs()));
            if yc < 0 || (yc == 0 && (xc < 0 || (xc == 0 && cc < 0))) { div *= -1 };

            let yc = yc / div;
            let xc = xc / div;
            let cc = cc / div;

            // Spara linjen, 2 ytterliggare punkter speglas i denna
            let line = (yc, xc, cc);
            *normal.entry(line).or_insert(0) += 2;
        }
    }

    for (line, n) in strike {
        *normal.entry(line).or_insert(0) += n;
    }

    let lines = normal.into_iter().collect::<Vec<_>>();

    // Hitta de störtsa speglingarna hittils
    let max = *lines.iter().map(|(_, n)| n).max().unwrap();
    let candidates = lines.into_iter()
        .filter(|(_, n)| *n == max).collect::<Vec<_>>();

    // Finns det en enskild punkt som ligger på symmetrilinjen?
    for ((yc, xc, cc), n) in candidates {
        let mut on_line = 0;

        for &(x, y) in points.iter(){
            if yc * y + xc * x + cc == 0 {
                on_line += 1;

                if on_line > 1 {
                    // Flera punkter låg på linjen, vi har redan räknat dessa (strike)
                    break;
                }
            }
        }

        // Vi hittade en punkt, detta måste vara den bästa symmetrin
        if on_line == 1 {
            println!("{}", n + 1);
            return
        }
    }

    println!("{}", max);
}
