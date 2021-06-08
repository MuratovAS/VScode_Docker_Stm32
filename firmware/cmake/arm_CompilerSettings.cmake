if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	#we put a minimum of optimizations for more convenient debugging, it is impossible without optimization at all, 
	#otherwise constexpr is not calculated, and this can cause a stack overflow (due to recursive functions)
	#set(DEBUG_OPTIMISATION "-fno-auto-inc-dec -fno-branch-count-reg -fno-combine-stack-adjustments \
	#						-fno-compare-elim -fno-cprop-registers -fno-dce -fno-defer-pop \
	#						-fno-delayed-branch -fno-dse -fno-forward-propagate -fno-guess-branch-probability \
	#						-fno-if-conversion -fno-if-conversion2 -fno-inline-functions-called-once \
	#						-fno-ipa-profile -fno-ipa-pure-const -fno-ipa-reference -fno-merge-constants \
	#						-fno-move-loop-invariants -fno-omit-frame-pointer -fno-reorder-blocks -fno-shrink-wrap \
	#						-fno-shrink-wrap-separate -fno-split-wide-types -fno-ssa-backprop -fno-ssa-phiopt \
	#						-fno-tree-bit-ccp -fno-tree-ccp -fno-tree-ch -fno-tree-coalesce-vars \
	#						-fno-tree-copy-prop -fno-tree-dce -fno-tree-dominator-opts -fno-tree-dse \
	#						-fno-tree-forwprop -fno-tree-fre -fno-tree-phiprop -fno-tree-pta \
	#						-fno-tree-scev-cprop -fno-tree-sink -fno-tree-slsr -fno-tree-sra \
	#						-fno-tree-ter -fno-unit-at-a-time")
							
	set(COMMON_FLAGS "-mtpcs-frame -mtpcs-leaf-frame -fno-omit-frame-pointer -O0 -specs=nosys.specs -specs=nano.specs")
	set(LINKER_FLAGS "-lc -lrdimon -u _printf_float")
else()
	set(COMMON_FLAGS "-ffat-lto-objects -fno-builtin")#-flto
	set(LINKER_FLAGS "-lc -lrdimon -u _printf_float")
endif()

set(WARNINGS "-Wall -Wextra") ## -Wno-comment -Wno-unused-parameter !!!-Werror

set(COMMON_FLAGS
"${CPU_FLAGS} ${FPU_FLAGS} -mthumb -mthumb-interwork -unaligned_access \
-ffunction-sections -fdata-sections -fno-common -fmessage-length=0 \
-finput-charset=UTF-8 ${COMMON_FLAGS} ${WARNINGS}")

SET(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -std=c++17 -Wno-register -fno-exceptions -frtti")
SET(CMAKE_C_FLAGS "${COMMON_FLAGS} -std=gnu18")
