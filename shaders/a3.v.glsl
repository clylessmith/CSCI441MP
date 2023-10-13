#version 410 core

// uniform inputs
uniform mat4 mvpMatrix;                 // the precomputed Model-View-Projection Matrix
// add normal matrix
uniform mat3 normalMatrix;

//add the model matrix
uniform mat4 modelMtx;

// add light uniforms
uniform vec3 lightDirection;
uniform vec3 lightColor;

uniform vec3 materialColor;             // the material color for our vertex (& whole object)

uniform vec3 cameraPosition;

uniform vec3 pointLightPos;

uniform int currentLight;

// attribute inputs
layout(location = 0) in vec3 vPos;      // the position of this specific vertex in object space
// add vertex normal
layout(location = 1) in vec3 vNormal;

// varying outputs
layout(location = 0) out vec3 color;    // color to apply to this vertex

void main() {

    vec3 viewDirection = normalize( cameraPosition - vPos);
    // transform & output the vertex in clip space
    gl_Position = mvpMatrix * vec4(vPos, 1.0);

    vec3 diffuse;
    vec3 specular;
    vec3 ambient;

    //DETERMINE LIGHT (7 point light, 8 directional, 9 spotlight)
    if(currentLight == 7){

        ////POINT LIGHT ////

        vec3 pointLightDirection = pointLightPos - vec3( modelMtx * vec4(vPos,1.0));

        vec3 lightVector = normalize(pointLightDirection);

        // transform normal vector
        vec3 vNormalNew =  normalize( normalMatrix * vNormal);

        // vec3 pointLightColor = ()

        // perform diffuse calculation
        diffuse = 0.5 * (materialColor * lightColor * max(dot(lightVector,  vNormalNew),0));

        vec3 reflectance =  0.05 * (-pointLightDirection + 2 * (max(dot(vNormalNew, pointLightDirection),0)) * vNormalNew);

        specular = 0.05 *( lightColor * materialColor * pow(max(dot(reflectance, viewDirection), 0),2));

        ambient = 0.2 * lightColor * materialColor;
        
        //END OF POINT LIGHT////

    }
    else if (currentLight == 8){
        //DIRECTION LIGHT ////
        // compute Light vector
        vec3 lightVector = -lightDirection / abs(lightDirection);

        // transform normal vector
        vec3 vNormalNew =  normalize( normalMatrix * vNormal);


        // perform diffuse calculation
        diffuse = 0.3 * (materialColor * lightColor * max(dot(lightVector,  vNormalNew),0));

        vec3 reflectance = 0.3 * (-lightDirection + 2 * (max(dot(vNormalNew, lightDirection),0)) * vNormalNew);
        specular = 0.05 *( lightColor * materialColor * pow(max(dot(reflectance, viewDirection), 0),20));

        ambient = 0.1 * lightColor * materialColor;
        //DIRECTIONAL LIGHT ////
        }

        // assign the color for this vertex
        color = diffuse  + specular + ambient;

}