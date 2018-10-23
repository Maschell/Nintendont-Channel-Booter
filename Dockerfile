FROM wiiulegacy/core:latest

# clear portlibs. just in case.
RUN rm -rf $DEVKITPRO/portlibs

# Get dependencies
COPY --from=wiiulegacy/dynamic_libs:latest /artifacts $DEVKITPRO/portlibs
COPY --from=wiiulegacy/libutils:0.1 /artifacts $DEVKITPRO/portlibs

WORKDIR project