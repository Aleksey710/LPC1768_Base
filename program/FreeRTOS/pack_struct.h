/// Compiler hints for packing lwip's structures
#define PACK_STRUCT_FIELD(x)    x __attribute__((packed))
#define PACK_STRUCT_STRUCT      __attribute__((packed))
#define PACK_STRUCT_BEGIN
#define PACK_STRUCT_END