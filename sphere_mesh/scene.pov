#include "sphere.inc"

  global_settings {
    radiosity {
      pretrace_start 0.08
      pretrace_end   0.04
      count 35

      nearest_count 5
      error_bound 1.8
      recursion_limit 3

      low_error_factor 0.5
      gray_threshold 0.0
      minimum_reuse 0.015
      brightness 1

      adc_bailout 0.01/2
    }
  }

  camera {
/*
mesh_camera { 100 1
mesh { generated_sphere }
}
location <0, 0, 0.1>
direction <0,0,1>
*/
    location <2, 2, -5>
    look_at <0, 0, 0>
  }


 light_source {
 <0, 2, 0>, color rgb <1.0 1.0 1.0>
 area_light <2, 0, 0>, <0, 0, 2>, 5 , 5
}


difference {
	   box {<-5.1, -5.1, -5.1>, <5.1, 5.1, 5.1>}
	   box {<-5, -2, -5>, <5, 2, 5>}
	texture {
 		pigment { rgb <1.0 0.01 0.2>}
		}
}

mesh { generated_sphere }



