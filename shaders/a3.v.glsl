#version 410 core

// uniform inputs
uniform mat4 mvpMatrix;                 // the precomputed Model-View-Projection Matrix
// add normal matrix
uniform mat3 normalMatrix;

// add light uniforms
uniform vec3 lightDirection;
uniform vec3 lightColor;

uniform vec3 materialColor;             // the material color for our vertex (& whole object)



// attribute inputs
layout(location = 0) in vec3 vPos;      // the position of this specific vertex in object space
// add vertex normal
layout(location = 1) in vec3 vNormal;

// varying outputs
layout(location = 0) out vec3 color;    // color to apply to this vertex

void main() {
    // transform & output the vertex in clip space
    gl_Position = mvpMatrix * vec4(vPos, 1.0);

    // compute Light vector
    vec3 lightVector = -lightDirection / abs(lightDirection);

    // transform normal vector
    vec3 vNormalNew =  normalize( normalMatrix * vNormal);


    // perform diffuse calculation
    // vec3 iDiffuse = lightColor * materialColor * (dot(lightVector, vNormalNew) > 0 ? dot(lightVector, vNormalNew) : 0);
    vec3 iDiffuse = 0.3 * (materialColor * lightColor * max(dot(lightVector,  vNormalNew),0));

    vec3 reflectance = 0.3 * (-lightDirection + 2 * (max(dot(vNormalNew, lightDirection),0)) * vNormalNew);
    vec3 ambient = 0.1 * lightColor * materialColor;


    // assign the color for this vertex
    color = iDiffuse  + reflectance+ ambient;
    // color = iDiffuse  + ambient;


}