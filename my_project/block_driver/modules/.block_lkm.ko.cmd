cmd_/home/block_driver/block_lkm.ko := ld -r -m elf_i386 -T /usr/src/kernels/linux-2.6.38.8/scripts/module-common.lds --build-id  -o /home/block_driver/block_lkm.ko /home/block_driver/block_lkm.o /home/block_driver/block_lkm.mod.o