#ifndef LIB_PSS_BITWISE_ENUM_H
#define LIB_PSS_BITWISE_ENUM_H 1

#define DefineBitwiseOperators(baseType, underlyingType) \
inline baseType operator&(baseType l, baseType r) { return (baseType)((underlyingType) l & (underlyingType) r); }; \
inline baseType operator&(baseType l, underlyingType r) { return (baseType)((underlyingType) l & (underlyingType) r); }; \
inline baseType operator&(underlyingType l, baseType r) { return (baseType)((underlyingType) l & (underlyingType) r); }; \
\
inline baseType operator|(baseType l, baseType r) { return (baseType)((underlyingType) l | (underlyingType) r); }; \
inline baseType operator|(underlyingType l, baseType r) { return (baseType)((underlyingType) l | (underlyingType) r); }; \
inline baseType operator|(baseType l, underlyingType r) { return (baseType)((underlyingType) l | (underlyingType) r); } \
\
inline baseType operator^(baseType l, baseType r) { return (baseType)((underlyingType)l ^ (underlyingType)r); }; \
inline baseType operator^(underlyingType l, baseType r) { return (baseType)((underlyingType)l ^ (underlyingType)r); }; \
inline baseType operator^(baseType l, underlyingType r) { return (baseType)((underlyingType)l ^ (underlyingType)r); } \
\
inline baseType operator>>(baseType l, baseType r) { return (baseType)((underlyingType)l >> (underlyingType)r); }; \
inline baseType operator>>(underlyingType l, baseType r) { return (baseType)((underlyingType)l >> (underlyingType)r); }; \
inline baseType operator>>(baseType l, underlyingType r) { return (baseType)((underlyingType)l >> (underlyingType)r); } \
\
inline baseType operator<<(baseType l, baseType r) { return (baseType)((underlyingType)l << (underlyingType)r); }; \
inline baseType operator<<(underlyingType l, baseType r) { return (baseType)((underlyingType)l << (underlyingType)r); }; \
inline baseType operator<<(baseType l, underlyingType r) { return (baseType)((underlyingType)l << (underlyingType)r); }



#endif