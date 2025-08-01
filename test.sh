# $1,     $2: compilers
# $3:     buildtype
# $4     stdc
# $5     stdcc

makers=("-GNinja" "")
lstdc=("90" "99" "11" "17" "23")
lstdcc=("98" "11" "14" "17" "20" "23")

__ae2f_CXX=("ON" "OFF")
__ae2f_IS_SHARED=("ON" "OFF")

buildtype=$3

echo "Generator: $generator"

for stdc in ${lstdc[@]}; do
for stdcc in ${lstdcc[@]}; do
for _ae2f_CXX in ${__ae2f_CXX[@]}; do
for _ae2f_IS_SHARED in ${__ae2f_IS_SHARED[@]}; do
for _maker in ${makers[@]}; do

builddir=build/B$buildtype$_maker$stdc$stdcc$_ae2f_CXX$_ae2f_IS_SHARED

cmake -S . -B $builddir \
    -DCMAKE_C_STANDARD=$stdc \
    -DCMAKE_CXX_STANDARD=$stdcc \
    $1 $2 \
    -Dae2f_CXX=$_ae2f_CXX \
    -Dae2f_IS_SHARED=$_ae2f_IS_SHARED  \
    $_maker \
    -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake \
    || { echo "Configuration failed"; exit 1; }


#-G "$generator Makefiles" 

cmake --build $builddir --config $buildtype || { echo "Build failed"; exit 1; }
ctest --test-dir $builddir -C $buildtype --output-on-failure || { echo "Test failed"; exit 1; }
rm -rf $builddir


done
done
done
done
done
