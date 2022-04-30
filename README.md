

# To do list:


- [x] load scans using CGAL .ply reader
- [x] measure distance between scans, then crop the last scan
- [ ] cluster pointcloud using cilantro or cgal
- [ ] take the largest scan and create the bounding-box around it
- [ ] crop cloud by the bounding-box
- [ ] compute normals
- [ ] cluster point-cloud by normals and take again the largest
- [ ] get color point segments and cluster by distance
- [ ] get convex hull around the found point cloud of the surface
- [ ] computer center of the shingle to get the robot plane



# Dependencies

Easy3d - visualizer`bash commands:

```
git clone https://github.com/LiangliangNan/Easy3D.git
cd Easy3D
cmake -S . -B Release -G "Visual Studio 16 2019" -A x64
```

* go to Release folder, open the project and change debug to release, then build, check example files
