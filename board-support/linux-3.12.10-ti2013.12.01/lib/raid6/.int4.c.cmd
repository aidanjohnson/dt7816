cmd_lib/raid6/int4.c := awk -f/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/lib/raid6/unroll.awk -vN=4 < lib/raid6/int.uc > lib/raid6/int4.c || ( rm -f lib/raid6/int4.c && exit 1 )
