

# To do list:

- [x] scanning using Faro Freestyline
![image](https://user-images.githubusercontent.com/18013985/166123129-1b49c8a7-bfa0-4def-8dd6-668b05690d81.png)
![image](https://user-images.githubusercontent.com/18013985/166123148-9071040b-667c-4b38-ba7e-70d32c51a4c1.png)

- [x] Scanning Using FARO Focus
![image](https://user-images.githubusercontent.com/98747079/179916599-ef9f1d3f-6914-4a02-ad02-e80fb4870d35.jpg)
![image](https://user-images.githubusercontent.com/98747079/179916689-25547f13-8b72-4b56-9a14-e47938cbdcd7.JPG)

-[x] Importing Open3d point cloud / Orienting to xy plane / Cropping with boundingbox
![image](https://user-images.githubusercontent.com/98747079/179917072-f7c442e1-e530-4b87-b157-8ee003fb1478.JPG)

-[x] Clustering by color using Cilantro/ Selecting the black marks based on cluster_intensities & Cropping the clouds by its boundingbox 
![image](https://user-images.githubusercontent.com/98747079/179917543-495dd1e8-8be7-4c36-b8a7-fbf448a10984.JPG)

-[x] Downsampling / Estimating normals/ Clustering based on connectedComponentKSearch / Selecting the last shingle
![image](https://user-images.githubusercontent.com/98747079/179918795-4ba43dec-7d6d-4ae8-9d3c-dc13c627036d.JPG)



- [] measure distance between scans, then crop the last scan
![image](https://user-images.githubusercontent.com/18013985/166123058-334763e7-9dab-4032-bcfc-f432a179c33b.png)
![image](https://user-images.githubusercontent.com/18013985/166123160-7ad23d20-4fbd-4da5-b8e1-0b7c52215015.png)




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
