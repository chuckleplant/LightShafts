#version 150


/// Our light scattering pass texture
uniform sampler2D UserMapSampler;
/// Indicate where is the light source on the screen (2D position)
uniform vec2 lightPositionOnScreen;

in vec2 varyingtexcoord;
out vec4 outputColor;


void main()
{
    vec2 tc = varyingtexcoord;
    //outputColor = vec4(lightPositionOnScreen.x, lightPositionOnScreen.y, 0.0, 1.0);
    //return;
    
    float decay=0.96815;
    float exposure=0.2;
    float density=0.926;
    float weight=0.58767;
    
    /// NUM_SAMPLES will describe the rays quality, you can play with
    int NUM_SAMPLES = 100;
    
    
    vec2 deltaTexCoord = (tc- lightPositionOnScreen.xy);
    
    //outputColor = texture(UserMapSampler, tc.xy);
    //return;
    
    deltaTexCoord *= 1.0 / float(NUM_SAMPLES) * density;
    float illuminationDecay = 1.0;
    
    vec4 color = texture(UserMapSampler, tc.xy) * 0.4;
    for(int i=0; i < NUM_SAMPLES ; i++)
    {
        tc -= deltaTexCoord;
        vec4 sample = texture(UserMapSampler, tc) * 0.4;
        sample *= illuminationDecay * weight;
        color += sample;
        illuminationDecay *= decay;
    }
    outputColor = color;
}
