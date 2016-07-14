#version 330
#pragma include "util.glsl"

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 textureMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform vec4 globalColor;

uniform vec4 startColor;
uniform vec4 endColor;

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inVelocity;
layout (location = 2) in float inAge;
layout (location = 3) in float inLifetime;

out vec4 positionVarying;
out vec4 colorVarying;

void main() {
    float elapsedTime = clamp(inAge / max(inLifetime, 1.0), 0.0, 1.0);
    
    positionVarying = vec4(inPosition, 1.0);
    
    vec3 color = mix(startColor.rgb, endColor.rgb, vec3(elapsedTime)); //map(vec3(sin(0.5 * PI * elapsedTime)), vec3(0.0), vec3(1.0), startColor.rgb, endColor.rgb);
//    vec3 color = smoothstep(vec3(0.0), vec3(1.0), vec3(elapsedTime));
    colorVarying = vec4(color, 1.0);
    
    gl_Position = modelViewProjectionMatrix * positionVarying;
    gl_PointSize = 5 * clamp((sin(PI * (float(inAge) / float(inLifetime + 1.0)))), 0.0, 1.0);
}