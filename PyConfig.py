import mod.ae2fPy.PreP.PreP as PreP
import os
import sys
import pathlib


HERE = os.path.dirname(os.path.abspath(__file__))
GIVEN_PATH = HERE if len(sys.argv) != 2 else sys.argv[1]

PRM_INCLUDE = [
    f"{HERE}/pyinclude/"
]

print("Hello World! BmpCLConfig is running...")
print(f"Current Position: {HERE}")
print(f"Given Path: {GIVEN_PATH}")


# Preprocess 0: Get all source and throw it to ...cl
for file in (f for f in pathlib.Path(f'{GIVEN_PATH}/').rglob('*.cl.c') if f.is_file()):
    FPATH : str = str(file.absolute())
    CTT : list[str]

    with open(FPATH, 'r') as F:
        CTT = F.readlines()


    SRC_RET = ["#define ae2fCL_Scenario\n"] + PreP.Include(CTT, str(file.parent.absolute()), PRM_INCLUDE)

    with open(FPATH[:len(FPATH) - 2], 'w') as F:
        F.writelines(SRC_RET)

    with open(FPATH[:len(FPATH) - 2] + "h", 'w') as F:
        LINES = [f'"' + LINE.replace('"', '\\"') + '"' for LINE in SRC_RET]
        F.writelines([f'"' + LINE.replace('"', '\\"')[:-1:] + '"\n' for LINE in SRC_RET])