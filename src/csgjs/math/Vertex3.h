#ifndef __CSGJS_VERTEX3__
#define __CSGJS_VERTEX3__

#include "csgjs/constants.h"
#include "csgjs/math/Vector3.h"
#include <iostream>

namespace csgjs {
  struct Vertex {
    Vector3 pos;

    Vertex() : pos() {
    }

    Vertex(const Vector3 &p) : pos(p) {}

    // if vertex had normal data or something like that, flip it here
    Vertex flipped() const {
      return *this;
    }

    Vertex interpolate(Vertex other, csgjs_real t) const {
      return Vertex(pos.lerp(other.pos, t));
    }

    Vertex transform(const Matrix4x4 &m) const {
      return Vertex(pos.transform(m));
    }


  };

  inline std::ostream& operator<<(std::ostream& os, const Vertex &v) {
    os << "pos: " << v.pos;
    return os;
  }
}

#endif
