import common;
import ui;

struct Vertex_Out {
    float4 position: SV_Position;
    float2 uv : TEXCOORD0;
};

[[vk::push_constant]]
ConstantBuffer<UIPC> pushConstant;

[[vk::binding(0, 1)]]
Texture2D colorTex;
[[vk::binding(0, 1)]]
SamplerState colorSampler;

[[shader("vertex")]]
Vertex_Out vertexMain(uint vertexID: SV_VertexID) {
    Vertex_Out outData;
    Vertex v = pushConstant.base.vertices[vertexID + pushConstant.base.vertexIndex];
    outData.position = mul(sceneData.m_WVP, float4(v.position, 1));
    outData.uv = float2(v.uv_x, v.uv_y);
    return outData;
}

[[shader("fragment")]]
float4 fragmentMain(Vertex_Out input) {
    return colorTex.Sample(colorSampler, input.uv);
}