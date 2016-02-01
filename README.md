## "Metaprogramming for dummies" presentation for [C++Now][] 2016

This repository contains my [reveal.js][]-based presentation on metaprogramming
for dummies for C++Now 2016.

## Basic usage
Go to https://ldionne.github.io/cppnow-2016-metaprogramming-for-dummies or
open `index.html` with your browser.

## Advanced usage
From the root of the repository,
```sh
npm install
grunt serve &
```

and then connect to `localhost:8000` to view locally.

## Notes to my future self
`index.html` is generated from `index.in.html`. To generate `index.html`,
```sh
mkdir build
cd build
cmake ..
make index
```

<!-- Links -->
[C++Now]: http://cppnow.org
[reveal.js]: https://github.com/hakimel/reveal.js