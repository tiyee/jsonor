//
// Created by tiyee on 2021/6/19.
//

#ifndef JSONOR_H
#define JSONOR_H


#include <vector>
#include <string>

typedef enum {
    UNKNOWN = 0,
    Bool,
    Byte,
    UBYTE,
    SHORT,
    USHORT,
    FLOAT,
    DOUBLE,
    INT,
    UINT,
    LONG,
    ULONG,
    STRING,
} kType;

typedef enum {

    VALUE = 1,
    PAIR = 2,
    ARRAY = 3,
    MAP = 4,
    OBJECT = 5,
} kForward;
typedef enum {
    PHP_JSON_ERROR_NONE = 0,
    PHP_JSON_ERROR_DEPTH,
    PHP_JSON_ERROR_STATE_MISMATCH,
    PHP_JSON_ERROR_CTRL_CHAR,
    PHP_JSON_ERROR_SYNTAX,
    PHP_JSON_ERROR_UTF8,
    PHP_JSON_ERROR_RECURSION,
    PHP_JSON_ERROR_INF_OR_NAN,
    PHP_JSON_ERROR_UNSUPPORTED_TYPE,
    PHP_JSON_ERROR_INVALID_PROPERTY_NAME,
    PHP_JSON_ERROR_UTF16,
    PHP_JSON_ERROR_NON_BACKED_ENUM,
} kErrCode;
struct Value {
    kType t;
    int seq; // TOTAL SEQUENCE
    void *p_val;
};
struct Pair {
    kForward forward;
    int seq; //  SEQUENCE IN CURRENT
    Value *k;
    void *v;
};
struct Item {
    kForward forward;
    int seq; //  SEQUENCE IN CURRENT
    void *v;
};
struct Object {
    int size;
    int seq;
    std::string name;
    std::vector<Item> children;
};
struct Array {
    int size;
    int seq;
    std::string name;
    std::vector<Item> children;
};
struct Map {
    int size;
    int seq;
    std::string name;
    std::vector<Pair> children;
};
struct Root {
    kForward forward;
    int size; //  SEQUENCE IN CURRENT
    void *v; // FORWARD PTR

};
struct Term {
    size_t start;
    size_t len;
    kForward t;
    Term *sg;
    void *v; // BIND STRUCT
};
typedef std::vector<Term> Terms;

kErrCode _json_parser(const Terms *&terms, const char *&json);

kErrCode json_decode(const Root *&root, const char *&json);

kErrCode json_encode(const char *&json, const Root *&root);


//**** privacy  format to storage or transmit for better perform   ****//


// seq+type+[length]+data
// if kv : seq+kv_type+[k_length]+key+v_length+value
kErrCode json_encode_custom(const char *&jsonjson_custom, const Root *&root);

kErrCode jso_decode_custom(const Root *&root, const char *&json_custom);

template<typename T>
kErrCode _digital_to_buff_custom(const char *&buff, const T *&data);

kErrCode _string_to_buff_custom(const char *&buff, const std::string *&str);

/**
 *  len <= 0x7F, use 1 byte for length encoding. the highest bit is 0, the remaining 7 bit is for length
 *  0x7F < len <= 0x3FFF, use 2 byte for length encoding, the highest two bit is 10, the remain 14 bit is for length
 *  len > 0x3FFF, use 4 byte for length encoding, the highest two bit is 11, the remain 30 bit is for length
 */
int _string_length_buff_custom(const char *&buff, size_t len);


#endif //JSONOR_H
