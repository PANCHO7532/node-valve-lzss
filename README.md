# node-valve-lzss
Node.JS bindings for Valve's LZSS compression codec

## Installing
Run `npm install node-valve-lzss` and you're good to go

Make sure to have installed an C++ compiler and `node-gyp`, you don't have it? Install with `npm install -g node-gyp` AND a compiler for your system before installing this.

## Usage
```js
const valveLZSS = require("node-valve-lzss");
// Compress
const compressedData = valveLZSS.compress(buffer); // returns <Buffer>
// Uncompress
const decompressedData = valveLZSS.uncompress(compressedData); // returns <Buffer>
// Detect if it's compressed
const isCompressed = valveLZSS.isCompressed(compressedData); // returns true or false
// Get Uncompressed size from compressed data
const getActualSize = valveLZSS.getActualSize(compressedData); // returns a number representing the size in bytes of uncompressed data
```
At compression, if you pass an string or ArrayBuffer it would be automatically converted into an Buffer.

## Before you use this
For unknown reasons, certain data can't be compressed and the library will throw an error detailing the reason at it's best

The solution to these cases is up to you, some tips would be padding the data, splitting into chunks, etc. Probably such errors would stay unfixed as I don't have the current knowledge yet to track these bugs and fix them in an appropriate way.

For your own sanity, please DON'T use this in production code UNLESS you know what are you doing.
### NOTE: This project was tested only on Linux systems, if you have Windows and can't install, feel free to open an issue.

## Contributions
Contributions are welcome! But please detail them as good as possible. Since this is an quite cryptic project and a lot of things can go wrong, you should do it.

## Credits
- [https://github.com/Leystryku/leysourceengineclient](https://github.com/Leystryku/leysourceengineclient) For the LZSS codec
- [https://github.com/SteamRE/open-steamworks](https://github.com/SteamRE/open-steamworks) For additional typedefs so the library could work