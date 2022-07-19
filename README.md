

# To do list:

- [x] scanning using Faro Freestyline
![image](https://user-images.githubusercontent.com/18013985/166123129-1b49c8a7-bfa0-4def-8dd6-668b05690d81.png)
![image](https://user-images.githubusercontent.com/18013985/166123148-9071040b-667c-4b38-ba7e-70d32c51a4c1.png)

- [x] Scanning Using FARO Focus
![image](https://user-images.githubusercontent.com/98747079/179799829-a63729fb-8ec5-443c-ba56-d84dec7233ba.JPG)

- [x] load scans using CGAL .ply reader
- [x] measure distance between scans, then crop the last scan
![image](https://user-images.githubusercontent.com/18013985/166123058-334763e7-9dab-4032-bcfc-f432a179c33b.png)
![image](https://user-images.githubusercontent.com/18013985/166123160-7ad23d20-4fbd-4da5-b8e1-0b7c52215015.png)

- [x] cluster pointcloud using cilantro or cgal
![image](https://user-images.githubusercontent.com/98747079/176932444-6b806dc0-3379-4c45-9f29-d8264f7efa3b.JPG)
- [x] take the largest scan and create the bounding-box around it
- [ ] crop cloud by the bounding-box
- [ ] compute normals
- [ ] cluster point-cloud by normals and take again the largest
- [ ] get color point segments and cluster by distance
- [ ] get convex hull around the found point cloud of the surface
- [ ] computer center of the shingle to get the robot plane



# Dependencies

## Visualizer - Easy3d

```
bash commands:

git clone https://github.com/LiangliangNan/Easy3D.git
cd Easy3D
cmake -S . -B Release -G "Visual Studio 16 2019" -A x64

go to Release folder, open the project and change debug to release, then build, check example files
```


## CGAL, Boost, Eigen - PointCloud load

```
download library and libraries: https://github.com/CGAL/cgal/releases/tag/v5.4
```
