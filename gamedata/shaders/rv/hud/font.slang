import common;

struct Vertex_Out {
    float4 position: SV_Position;
    float4 color : TEXCOORD0;
    float2 uv : TEXCOORD1;
};

[[vk::push_constant]]
ConstantBuffer<BasePushConstantData> pushConstant;

[[vk::binding(0, 1)]]
Texture2D fontTex;
[[vk::binding(0, 1)]]
SamplerState fontSampler;

[[shader("vertex")]]
Vertex_Out vertexMain(uint vertexID: SV_VertexID) {
    Vertex_Out outData;
    Vertex v = pushConstant.vertices[vertexID + pushConstant.vertexIndex];
    outData.position = mul(sceneData.m_WVP, float4(v.position, 1));
    outData.uv = float2(v.uv_x, v.uv_y);
    outData.color = v.color;
    return outData;
}

[[shader("fragment")]]
float4 fragmentMain(Vertex_Out input) {
    float4 texel = fontTex.Sample(fontSampler, input.uv);

    if (any(texel.rgb))
        return float4(input.color.rgb, texel.a + input.color.a);
    else
        return float4(0);
    
    // texel.rgb = input.color.rgb;
    // texel.a *= input.color.a;
    // return texel;
    // if (any(texel.rgb))
    //     return float4(input.color.rgb * texel.rgb, texel.a);
    // else
    //     return float4(0);
}