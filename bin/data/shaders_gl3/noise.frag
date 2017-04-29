#version 150


/// Our light scattering pass texture
uniform sampler2D UserMapSampler;
uniform sampler2D SceneSampler;

/// Indicate where is the light source on the screen (2D position)
uniform vec2 lightPositionOnScreen;


// Base values
//
//float decay=0.96815;
//float exposure=0.2;
//float density=0.926;
//float weight=0.58767;
uniform float decay;
uniform float exposure;
uniform float density;
uniform float weight;
//
// numSamples = 100;
uniform int numSamples;

in vec2 varyingtexcoord;
out vec4 outputColor;


void main()
{

    vec2 tc = varyingtexcoord;
    vec4 sceneColor = texture(SceneSampler, tc);
    vec2 deltaTexCoord = (tc - lightPositionOnScreen.xy);
    deltaTexCoord *= 1.0 / float(numSamples) * density;
    float illuminationDecay = 1.0;
    vec4 color = texture(UserMapSampler, tc.xy) * 0.4;
    for(int i=0; i < numSamples ; i++)
    {
        tc -= deltaTexCoord;
        vec4 sample = texture(UserMapSampler, tc) * 0.4;
        sample *= illuminationDecay * weight;
        color += sample;
        illuminationDecay *= decay;
    }
    outputColor = sceneColor + color;
}
