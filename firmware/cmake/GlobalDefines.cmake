# universal definitions
add_definitions(
        -D__WEAK=__attribute__\(\(weak\)\)
        "-D__INLINE=__attribute__\(\(always_inline\)\) inline"
        -D__UNUSED=__attribute__\(\(unused\)\)
        
        -D__PACKED_2=__attribute__\(\(__packed__,__aligned__\(2\)\)\)
        -D__PACKED_4=__attribute__\(\(__packed__,__aligned__\(4\)\)\)
        -D__PACKED_8=__attribute__\(\(__packed__,__aligned__\(8\)\)\)

        -D__CCMRAM=__attribute__\(\(section\(\".ccmram\"\)\)\)
        -D__SRAM=__attribute__\(\(section\(\".sram\"\)\)\)
)