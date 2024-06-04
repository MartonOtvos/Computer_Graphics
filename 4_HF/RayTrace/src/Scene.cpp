//
// Created by Marci on 6/1/2024.
//

#include "Scene.h"

vec3 Scene::DirectLight(Hit hit) {
    vec3 outRad = hit.material->ka * La;

    for(unsigned int i = 0; i < lights.size(); i++){
        Ray shadowRay(hit.position, lights[i]->direction, false);
        Hit shadowHit = FirstIntersect(shadowRay);
        if(shadowHit.t < 0 || shadowHit.t > length(hit.position - lights[i]->Le);

    }



    return vec3();
}

vec3 Scene::Trace(Ray ray, int depth) {


    return vec3();
}

Hit Scene::FirstIntersect(Ray ray) {


    return Hit();
}

Scene::Scene() {


}

void Scene::Build() {


}

vector<vec4> Scene::Render() {


    return vector<vec4>();
}


