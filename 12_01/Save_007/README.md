# Save 007

## If you can run shell document
Just run `Launch.sh`, which will do the following process:
1. get into the current foldpath
2. run `Sprinkle_Points.py` to generate the necessary data with a guide picture `points.png`
3. compile `Save_007.cpp` into executable file `Save_007`
4. check if `path.txt` exist in the current foldpath, if exists, then remove it
5. run the executable file `Save_007` and store its output into `path.txt`
6. run `Draw_Path.py` to show one way that 007 could choose, if there exists no way out, then some information will show

## If you can NOT run shell document
Just run the following commands in order:
1. cd 
