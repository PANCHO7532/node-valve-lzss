/*
 * /====================================================================\
 * | Valve LZSS wrapper                                                 |
 * | Copyright (c) PANCHO7532 [pancho7532@p7com.net] 2022               |
 * |====================================================================|
 * |-> Purpose: Main file for the wrapper                               |
 * \====================================================================/
 */
const native = require("bindings")("valveLZSS");
module.exports = {
    compress(buffer) {
        if(!buffer) { throw "You can't leave the buffer parameter empty."; }
        if(typeof buffer == "string" || buffer instanceof Array) {
            buffer = Buffer.from(buffer);
            return native.compress(buffer);
        } else {
            return native.compress(buffer);
        }
    },
    uncompress(buffer) {
        if(!buffer) { throw "You can't leave the buffer parameter empty."; }
        return native.uncompress(buffer);
    },
    isCompressed(buffer) {
        if(!buffer) { throw "You can't leave the buffer parameter empty."; }
        return native.isCompressed(buffer);
    },
    getActualSize(buffer) {
        if(!buffer) { throw "You can't leave the buffer parameter empty."; }
        return native.getActualSize(buffer);
    }
};