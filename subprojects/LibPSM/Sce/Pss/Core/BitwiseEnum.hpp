#ifndef LIB_PSS_BITWISE_ENUM_H
#define LIB_PSS_BITWISE_ENUM_H 1

#define DEFINE_BITWISE_OPERATORS(BT, UT) \
inline BT operator&(BT l, BT r) { return (BT)((UT) l & (UT) r); }; \
inline BT operator&(BT l, UT r) { return (BT)((UT) l & (UT) r); }; \
inline BT operator&(UT l, BT r) { return (BT)((UT) l & (UT) r); }; \
\
inline BT operator|(BT l, BT r) { return (BT)((UT) l | (UT) r); }; \
inline BT operator|(UT l, BT r) { return (BT)((UT) l | (UT) r); }; \
inline BT operator|(BT l, UT r) { return (BT)((UT) l | (UT) r); } \
\
inline BT operator^(BT l, BT r) { return (BT)((UT)l ^ (UT)r); }; \
inline BT operator^(UT l, BT r) { return (BT)((UT)l ^ (UT)r); }; \
inline BT operator^(BT l, UT r) { return (BT)((UT)l ^ (UT)r); } \
\
inline BT operator>>(BT l, BT r) { return (BT)((UT)l >> (UT)r); }; \
inline BT operator>>(UT l, BT r) { return (BT)((UT)l >> (UT)r); }; \
inline BT operator>>(BT l, UT r) { return (BT)((UT)l >> (UT)r); } \
\
inline BT operator<<(BT l, BT r) { return (BT)((UT)l << (UT)r); }; \
inline BT operator<<(UT l, BT r) { return (BT)((UT)l << (UT)r); }; \
inline BT operator<<(BT l, UT r) { return (BT)((UT)l << (UT)r); }; \
\
inline BT operator|=(BT& l, BT r) { return l = (BT)((UT)l | (UT)r); }; \
inline BT operator&=(BT& l, BT r) { return l = (BT)((UT)l & (UT)r); }; \
inline BT operator^=(BT& l, BT r) { return l = (BT)((UT)l ^ (UT)r); }; \
inline BT operator>>=(BT& l, BT r) { return l = (BT)((UT)l >> (UT)r); }; \
inline BT operator<<=(BT& l, BT r) { return l = (BT)((UT)l << (UT)r); }; 


#endif