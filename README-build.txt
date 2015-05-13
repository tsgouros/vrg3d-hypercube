
To Build:

ssh login001    // you can't build on cave001
module load cave
module load nvidia-driver
module load vrpn
source envars   // to get CS G, GARCH, and the new VRG3D_BASE settings
make clean
make


To run in YURT:

use Kiosk and run "Hypercube", or from comand line:

ssh cave001
module load cave
module load nvidia-driver
module load vrpn
run-cave ./hypercube


To stop:

Use kiosk and click "skull-crossbones" after starting Hypercube

ssh cave001
module load cave
module load nvidia-driver
module load vrpn
stop hypercube

