# $1,     $2: compilers
# $3:     buildtype
# $4     stdc
# $5     stdcc

# makers=("")
# buildtypes=("Release" "Debug" "MinSizeRel" "RelWithDebInfo")
lstdc=("90" "99" "11" "17" "23")
lstdcc=("17" "20" "23")

__ae2f_CXX=("ON" "OFF")
__ae2f_IS_SHARED=("ON" "OFF")

buildtype=$3

for stdc in ${lstdc[@]}; do
for stdcc in ${lstdcc[@]}; do
for _ae2f_CXX in ${__ae2f_CXX[@]}; do
for _ae2f_IS_SHARED in ${__ae2f_IS_SHARED[@]}; do

builddir=build/B$buildtype$stdc$stdcc$makers$_ae2f_CXX$_ae2f_IS_SHARED

cmake -S . -B $builddir \
    -DCMAKE_C_STANDARD=$stdc \
    -DCMAKE_CXX_STANDARD=$stdcc \
    $1 $2 \
    -DCMAKE_MAKE_PROGRAM=make \
    -Dae2f_CXX=$_ae2f_CXX \
    -Dae2f_IS_SHARED=$_ae2f_IS_SHARED || { echo "Configuration failed"; exit 1; }

cmake --build $builddir --config $buildtype || { echo "Build failed"; exit 1; }
ctest --test-dir $builddir -C $buildtype --output-on-failure || { echo "Test failed"; exit 1; }

done
done
done
done
