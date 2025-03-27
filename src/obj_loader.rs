use cookie_lib_rust::matrix::Matrix;
use cookie_lib_rust::vector::Vector2D;
use cookie_lib_rust::vector::Vector3D;

struct Face {
    vertices_id:    Vec<i64>,
    textures_id:    Vec<i64>,
    normals_id:     Vec<i64>,
}

pub struct Obj {
    vertices:       Vec<Vector3D<f64>>,
    textures:       Vec<Vector2D<f64>>,
    normals:        Vec<Vector3D<f64>>,
    faces:          Vec<Face>,
    position:       Matrix<f64>,
    rotation:       Matrix<f64>,
}

impl Obj {
    pub fn new() {
        Obj {}
    }
}
