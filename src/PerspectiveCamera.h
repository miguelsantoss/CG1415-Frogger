#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "Camera.h"

class PerspectiveCamera : public Camera {
public:
  PerspectiveCamera(double fovy, double aspect, double zNear, double zFar);
  ~PerspectiveCamera();
  void update();
  void computeProjectionMatrix();
  void computeVisualizationMatrix();
private:
	double _fovy;
	double _aspect;
};

#endif