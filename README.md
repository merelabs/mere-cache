# mere-cache
An simple utility library contains common cache policy implementation that are used in mere projects. 

### policy
- fifo
- lifo
- lru
- lfu
- mru
- arc

## requires
`mere-cache` requires following componnets
- C++11 

## required
`mere-cache` is required by following app, utility and libaries,
- [mere-link-cache](https://github.com/merelabs/mere-link-cache)
- [mere-xdg](https://github.com/merelabs/mere-xdg)
- [mere-finder-app](https://github.com/merelabs/mere-finder-app)

## build ##
```
$ git clone https://github.com/merelabs/mere-cache.git
$ qmake
$ make
$ make install
```

### support
If you find a bug, or have a feature suggestion, please [log an issue](https://github.com/merelabs/mere-cache/issues). If you'd like to
contribute, please read [How to Contribute](CONTRIBUTING.md).

## license ##
All the code in this repository is licensed under a [BSD-2-Clause License](LICENSE).
