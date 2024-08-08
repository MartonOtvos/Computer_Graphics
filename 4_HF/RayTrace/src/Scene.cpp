//
// Created by Marci on 6/1/2024.
//

#include <iostream>
#include "Scene.h"
#include "Plane.h"
#include "Cylinder.h"
#include "Cone.h"

vec3 Scene::DirectLight(Hit hit, Ray ray) {
    vec3 outRad = hit.material->ka * La;
    for(auto & light : lights){
        vec3 Ll = normalize(light->direction);
        Ray shadowRay(hit.position + hit.normal * epsilon, Ll, true);
        Hit shadowHit = FirstIntersect(shadowRay);
        if(shadowHit.t < 0){

            float cosTheta = dot(Ll, hit.normal);
            vec3 diffuse;
            if(cosTheta < 0){
                diffuse = vec3(0,0,0);
            } else diffuse = light->Le * hit.material->kd * cosTheta;


            vec3 H = normalize(-ray.direction + Ll);
            float cosDelta = dot(hit.normal,H);

            vec3 specular = vec3(0,0,0);
            if(cosDelta > 0){
                specular = light->Le * hit.material->ks * powf( cosDelta, hit.material->shine );
            }
            outRad = outRad + diffuse + specular;
        }
    }
    return outRad;
}
int tracecount = 0;

vec3 Scene::Trace(Ray ray, int depth) {
    if(depth++ > 5) return La;
    Hit hit = FirstIntersect(ray);
    if(hit.t < 0) return La;

    vec3 outRad = vec3(0,0,0);

    //ROUGH
    if(hit.material->rough) outRad = DirectLight(hit, ray);

    //REFLECTIVE
    if(hit.material->reflective){
        vec3 reflectionDir = smoothSurfaceFunctions::reflect(ray.direction, hit.normal);
        Ray reflectRay(hit.position + hit.normal*epsilon, reflectionDir, ray.out);
        outRad = outRad + Trace(reflectRay, depth) * smoothSurfaceFunctions::Fresnel(ray.direction, hit.normal, hit.material->n, hit.material->k); //FRESNEL COULD BE BAD HERE
    }

    //REFRACTIVE
    if(hit.material->refractive){
        float ior = (ray.out) ? hit.material->n.x : 1/hit.material->n.x;
        vec3 refractionDir = smoothSurfaceFunctions::refract(ray.direction, hit.normal, ior);

        if(length(refractionDir) > 0){
            Ray refractRay(hit.position - hit.normal*epsilon, refractionDir, !ray.out);
            outRad = outRad + Trace(refractRay, depth) * vec3(1,1,1) - smoothSurfaceFunctions::Fresnel(ray.direction, hit.normal, hit.material->n, hit.material->k); //FRESNEL COULD BE BAD HERE
        }
    }

    return outRad;
}

Hit Scene::FirstIntersect(Ray ray) {
    Hit bestHit = Hit();
    for(Intersectable* object : objects){
        Hit currentHit = object->Intersect(ray);
        if(currentHit.t > 0 && (bestHit.t < 0 || currentHit.t < bestHit.t)) bestHit = currentHit;
    }
    if (dot(ray.direction, bestHit.normal) > 0) bestHit.normal = bestHit.normal * (-1);
    return bestHit;
}

Scene::Scene() {


}

void Scene::Build() {
    camera = new Camera3D;
    float fov = 45 * (M_PI / 180);
    camera->Set(vec3(0,1,4), vec3(0,0,0), vec3(0,1,0), fov);
    La = vec3(0.4,0.4,0.4);
    lights.push_back(new DirectionalLight(vec3(1,1,1),vec3(2,2,2)));

    Material* mat1 = new Material(0,0,0,vec3(0,0.3,0.9),vec3(0,0.1,0.3),vec3(0,0,0),false,false,true);
    Material* mat2 = new Material(0,0,0,vec3(0.9,0.9,0.9),vec3(0.3,0.3,0.3),vec3(0,0,0),false,false,true);
    //objects.push_back(new Sphere(vec3(0,0,0),1,mat1));
    objects.push_back(new Plane(mat1,mat2,vec3(0,1,0),vec3(0,-1,0)));

    mat1 = new Material(0,0,50.0f,vec3(0.9,0.6,0.3),vec3(0.3,0.2,0.1),vec3(2.0f,2.0f,2.0f),false,false,true);
    objects.push_back(new Cylinder(mat1,vec3(0,1,0.1),vec3(-1,-1,0),0.3f,2.0f));

    mat1 = new Material(vec3(0.17f, 0.35f, 1.5f),vec3(3.1f, 2.7f, 1.9f),0,vec3(0,0,0),vec3(0,0,0),vec3(0,0,0),true,false,false);
    objects.push_back(new Cylinder(mat1,vec3(0.1,1,0),vec3(1,-1,0),0.3f,2.0f));

    mat1 = new Material(vec3(1.3f, 1.3f, 1.3f),vec3(0, 0, 0),0,vec3(0,0,0),vec3(0,0,0),vec3(0,0,0),true,true,false);
    objects.push_back(new Cylinder(mat1,vec3(-0.2,1,-0.1),vec3(0,-1,-0.8),0.3f,2.0f));

    mat1 = new Material(0,0,100.0f,vec3(0.3,0.6,0.9),vec3(0.1,0.2,0.3),vec3(2.0f,2.0f,2.0f),false,false,true);
    objects.push_back(new Cone(mat1,vec3(-0.1, -1, -0.05),vec3(0,1,0),2,0.2f));

    mat1 = new Material(0,0,20.0f,vec3(0.9,0,0.6),vec3(0.3,0,0.2),vec3(2.0f,2.0f,2.0f),false,false,true);
    objects.push_back(new Cone(mat1,vec3(0.2, -1, 0),vec3(0,1,0.8),2,0.2f));
}

vector<vec4> Scene::Render() {
    long timerStart = glutGet(GLUT_ELAPSED_TIME);
    vector<vec4> image(windowWidth * windowHeight);
    for(unsigned int Y = 0; Y < windowHeight; Y++){
#pragma omp paralell for
        for(unsigned int X = 0; X < windowWidth; X++){
            vec3 color = Trace(camera->GetRay(X,Y), 0);
            image[Y * windowWidth + X] = vec4(color.x,color.y,color.z,1);

        }
    }

    printf("Rendering Time: %ld milliseconds\n",glutGet(GLUT_ELAPSED_TIME) - timerStart);
    return image;
}

void Scene::MoveOne() {
    camera->Animate(1);

}


