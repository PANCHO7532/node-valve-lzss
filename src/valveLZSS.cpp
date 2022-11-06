/*
 * /====================================================================\
 * | Valve LZSS wrapper                                                 |
 * | Copyright (c) PANCHO7532 [pancho7532@p7com.net] 2022               |
 * |====================================================================|
 * |-> Purpose: Main file for the library                               |
 * \====================================================================/
 */
#include <nan.h>
#include "include/disableWCF.h"
#include "include/clzss.h"

NAN_METHOD(compress) {
    if(info.Length() < 1) { Nan::ThrowError("You need to specify an Buffer class data as first parameter."); }
    if(!node::Buffer::HasInstance(info[0])) { Nan::ThrowError("You can only pass Buffer class data into this parameter."); }
    CLZSS clzssInstance;
    v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
    v8::Local<v8::Object> buffer = info[0]->ToObject(context).ToLocalChecked();
    unsigned char* rawDataInput = (unsigned char*) node::Buffer::Data(buffer);
    unsigned int rawDataLength = node::Buffer::Length(buffer);
    unsigned int uncompressedDataLength = 0;
    unsigned char* rawDataOutput = clzssInstance.Compress(rawDataInput, rawDataLength, &uncompressedDataLength);
    if(!!rawDataOutput) {
        v8::Local<v8::Object> newBuffer = Nan::NewBuffer(uncompressedDataLength).ToLocalChecked();
        memcpy(node::Buffer::Data(newBuffer), rawDataOutput, uncompressedDataLength);
        delete rawDataOutput;
        info.GetReturnValue().Set(newBuffer);
    } else {
        switch(clzssInstance.ErrorCode) {
            case 0:
                // Not really sure how we would get this
                Nan::ThrowError("Compression failed.");
                break;
            case 1:
                Nan::ThrowError("Compression failed, buffer size is less or equal to lzss_header_t.");
                break;
            case 2:
                Nan::ThrowError("Compression failed, unstable or worse results."); // ?
                break;
            case 3:
                Nan::ThrowError("Compression failed, unexpected failure.");
                break;
            default:
                Nan::ThrowError("Compression failed, unexpected error value.");
                break;
        }
        
    }
}
NAN_METHOD(uncompress) {
    if(info.Length() < 1) { Nan::ThrowError("You need to specify an Buffer class data as first parameter."); }
    if(!node::Buffer::HasInstance(info[0])) { Nan::ThrowError("You can only pass Buffer class data into this parameter."); }
    CLZSS clzssInstance;
    v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
    v8::Local<v8::Object> buffer = info[0]->ToObject(context).ToLocalChecked();
    unsigned char* rawDataInput = (unsigned char*) node::Buffer::Data(buffer);
    if(!clzssInstance.IsCompressed(rawDataInput)) { Nan::ThrowError("Data is not compressed or is invalid."); }
    unsigned int uncompressedDataLength = clzssInstance.GetActualSize(rawDataInput);
    unsigned char *rawDataOutput = new unsigned char[uncompressedDataLength];
    clzssInstance.Uncompress(rawDataInput, rawDataOutput);
    // Return the decompressed value
    v8::Local<v8::Object> newBuffer = Nan::NewBuffer(uncompressedDataLength).ToLocalChecked();
    memcpy(node::Buffer::Data(newBuffer), rawDataOutput, uncompressedDataLength);
    delete[] rawDataOutput;
    info.GetReturnValue().Set(newBuffer);
}
NAN_METHOD(isCompressed) {
    if(info.Length() < 1) { Nan::ThrowError("You need to specify an Buffer class data as first parameter."); }
    if(!node::Buffer::HasInstance(info[0])) { Nan::ThrowError("You can only pass Buffer class data into this parameter."); }
    CLZSS clzssInstance;
    v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
    v8::Local<v8::Object> buffer = info[0]->ToObject(context).ToLocalChecked();
    unsigned char* rawDataInput = (unsigned char*) node::Buffer::Data(buffer);
    info.GetReturnValue().Set(clzssInstance.IsCompressed(rawDataInput));
}
NAN_METHOD(getActualSize) {
    if(info.Length() < 1) { Nan::ThrowError("You need to specify an Buffer class data as first parameter."); }
    if(!node::Buffer::HasInstance(info[0])) { Nan::ThrowError("You can only pass Buffer class data into this parameter."); }
    CLZSS clzssInstance;
    v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();
    v8::Local<v8::Object> buffer = info[0]->ToObject(context).ToLocalChecked();
    unsigned char* rawDataInput = (unsigned char*) node::Buffer::Data(buffer);
    if(!clzssInstance.IsCompressed(rawDataInput)) { Nan::ThrowError("Data is not compressed or is invalid."); }
    info.GetReturnValue().Set(clzssInstance.GetActualSize(rawDataInput));
}
NAN_MODULE_INIT(initModule) {
    Nan::SetMethod(target, "compress", compress);
    Nan::SetMethod(target, "uncompress", uncompress);
    Nan::SetMethod(target, "isCompressed", isCompressed);
    Nan::SetMethod(target, "getActualSize", getActualSize);
}
DISABLE_WCAST_FUNCTION_TYPE
NODE_MODULE(valveLZSS, initModule)
DISABLE_WCAST_FUNCTION_TYPE_END