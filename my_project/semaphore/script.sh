# /bin/bash
for var in {1..100}
do
./rc1 &
./rc2 &
./rc3 &
done
exit 0
