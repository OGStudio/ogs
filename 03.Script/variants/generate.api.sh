FEATURE generate/Impl
echo "Generate embeddable api.lua.h"
cd $DIR/$STAGE/ogs-$PLATFORM
xxd -i api.lua{,.h}
