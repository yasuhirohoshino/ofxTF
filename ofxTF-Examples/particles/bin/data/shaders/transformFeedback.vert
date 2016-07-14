#version 330

#define PI 3.14159265358979

#pragma include "util.glsl"
#pragma include "noise.glsl"

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inVelocity;
layout (location = 2) in float inAge;
layout (location = 3) in float inLifetime;

out vec3 outPosition;
out vec3 outVelocity;
out float outAge;
out float outLifetime;

uniform float time;
uniform float timestep;
uniform float scale;
uniform float maxLifetime;

void main() {
    vec3 pos = inPosition;
    vec3 vel = inVelocity;
    float age = inAge;
    float lifetime = inLifetime;
    
    if(age >= lifetime){
        lifetime = 1.0 + maxLifetime * random(pos.xx);
        age = 0;
        vel.xyz = normalize(pos) * random(pos.zz);
        float phi = random(pos.xy) * PI;
        float theta = random(pos.yz) * PI * 2.0;
        float radius = random(pos.zx) * 5.0;
		pos = vec3(sin(phi) * cos(theta), sin(phi) * sin(theta), cos(phi)) * radius;
    }else{
        vel.x += snoise(vec4(pos.x * scale, pos.y * scale, pos.z * scale, 0.1352 * time)) * timestep;
        vel.y += snoise(vec4(pos.x * scale, pos.y * scale, pos.z * scale, 1.2814 * time)) * timestep;
        vel.z += snoise(vec4(pos.x * scale, pos.y * scale, pos.z * scale, 2.5564 * time)) * timestep;
        pos += vel;
        age++;
    }
    
    outPosition = pos;
    outVelocity = vel;
    outAge = age;
    outLifetime = lifetime;
}