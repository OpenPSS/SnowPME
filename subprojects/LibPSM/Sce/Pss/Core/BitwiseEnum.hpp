#ifndef LIB_PSS_BITWISE_ENUM_H
#define LIB_PSS_BITWISE_ENUM_H 1

#define DEFINE_BITWISE_ENUM_OPERATOR(BaseType, UnderlyingType) \
inline BaseType operator&(BaseType l, BaseType r) { return (BaseType)((UnderlyingType) l & (UnderlyingType) r); }; \
inline BaseType operator&(BaseType l, UnderlyingType r) { return (BaseType)((UnderlyingType) l & (UnderlyingType) r); }; \
inline BaseType operator&(UnderlyingType l, BaseType r) { return (BaseType)((UnderlyingType) l & (UnderlyingType) r); }; \
\
inline BaseType operator|(BaseType l, BaseType r) { return (BaseType)((UnderlyingType) l | (UnderlyingType) r); }; \
inline BaseType operator|(UnderlyingType l, BaseType r) { return (BaseType)((UnderlyingType) l | (UnderlyingType) r); }; \
inline BaseType operator|(BaseType l, UnderlyingType r) { return (BaseType)((UnderlyingType) l | (UnderlyingType) r); } \
\
inline BaseType operator^(BaseType l, BaseType r) { return (BaseType)((UnderlyingType)l ^ (UnderlyingType)r); }; \
inline BaseType operator^(UnderlyingType l, BaseType r) { return (BaseType)((UnderlyingType)l ^ (UnderlyingType)r); }; \
inline BaseType operator^(BaseType l, UnderlyingType r) { return (BaseType)((UnderlyingType)l ^ (UnderlyingType)r); } \
\
inline BaseType operator>>(BaseType l, BaseType r) { return (BaseType)((UnderlyingType)l >> (UnderlyingType)r); }; \
inline BaseType operator>>(UnderlyingType l, BaseType r) { return (BaseType)((UnderlyingType)l >> (UnderlyingType)r); }; \
inline BaseType operator>>(BaseType l, UnderlyingType r) { return (BaseType)((UnderlyingType)l >> (UnderlyingType)r); } \
\
inline BaseType operator<<(BaseType l, BaseType r) { return (BaseType)((UnderlyingType)l << (UnderlyingType)r); }; \
inline BaseType operator<<(UnderlyingType l, BaseType r) { return (BaseType)((UnderlyingType)l << (UnderlyingType)r); }; \
inline BaseType operator<<(BaseType l, UnderlyingType r) { return (BaseType)((UnderlyingType)l << (UnderlyingType)r); }; \
\
inline BaseType operator|=(BaseType& l, BaseType r) { return l = (BaseType)((UnderlyingType)l | (UnderlyingType)r); }; \
inline BaseType operator&=(BaseType& l, BaseType r) { return l = (BaseType)((UnderlyingType)l & (UnderlyingType)r); }; \
inline BaseType operator^=(BaseType& l, BaseType r) { return l = (BaseType)((UnderlyingType)l ^ (UnderlyingType)r); }; \
inline BaseType operator>>=(BaseType& l, BaseType r) { return l = (BaseType)((UnderlyingType)l >> (UnderlyingType)r); }; \
inline BaseType operator<<=(BaseType& l, BaseType r) { return l = (BaseType)((UnderlyingType)l << (UnderlyingType)r); }; \
\
inline BaseType operator *(BaseType l, BaseType r) { return (BaseType)((UnderlyingType)l * (UnderlyingType)r); }; \
inline BaseType operator +(BaseType l, BaseType r) { return (BaseType)((UnderlyingType)l + (UnderlyingType)r); }; \
inline BaseType operator -(BaseType l, BaseType r) { return (BaseType)((UnderlyingType)l - (UnderlyingType)r); }; \
\
inline BaseType operator *=(BaseType l, BaseType r) { return l = (BaseType)((UnderlyingType)l * (UnderlyingType)r); }; \
inline BaseType operator +=(BaseType l, BaseType r) { return l = (BaseType)((UnderlyingType)l + (UnderlyingType)r); }; \
inline BaseType operator -=(BaseType l, BaseType r) { return l = (BaseType)((UnderlyingType)l - (UnderlyingType)r); }; \
\
inline UnderlyingType operator *(UnderlyingType l, BaseType r) { return (UnderlyingType)((UnderlyingType)l * (UnderlyingType)r); }; \
inline UnderlyingType operator +(UnderlyingType l, BaseType r) { return (UnderlyingType)((UnderlyingType)l + (UnderlyingType)r); }; \
inline UnderlyingType operator -(UnderlyingType l, BaseType r) { return (UnderlyingType)((UnderlyingType)l - (UnderlyingType)r); }; \
\
inline UnderlyingType operator *(BaseType l, UnderlyingType r) { return (UnderlyingType)((UnderlyingType)l * (UnderlyingType)r); }; \
inline UnderlyingType operator +(BaseType l, UnderlyingType r) { return (UnderlyingType)((UnderlyingType)l + (UnderlyingType)r); }; \
inline UnderlyingType operator -(BaseType l, UnderlyingType r) { return (UnderlyingType)((UnderlyingType)l - (UnderlyingType)r); }; \
\
inline BaseType operator ~(BaseType l) { return (BaseType)(~(UnderlyingType)(l)); }; \
\
inline UnderlyingType operator ==(UnderlyingType l, BaseType r) { return (UnderlyingType)l == (UnderlyingType)r; }; \
inline UnderlyingType operator ==(BaseType l, UnderlyingType r) { return (UnderlyingType)l == (UnderlyingType)r; }; \

#endif