import common;
import ui;

struct Vertex_Out {
    float4 position: SV_Position;
    float3 uvl : TEXCOORD0;
};

[[vk::binding(0, 1)]]
Texture2DArray baseTex;
[[vk::binding(0, 1)]]
SamplerState baseTexSampler;

[[vk::push_constant]]
ConstantBuffer<UIPC> pushConstant;

[[shader("vertex")]]
Vertex_Out vertexMain(uint vertexID: SV_VertexID) {
  Vertex_Out o;
  Vertex v = pushConstant.base.vertices[vertexID + pushConstant.base.vertexIndex];
  o.position = mul(sceneData.m_WVP, float4(v.position, 1));
  o.uvl = float3(v.uv_x, v.uv_y, pushConstant.layerIndex);
  return o;
}

[[shader("fragment")]]
float4 fragmentMain(Vertex_Out input) {
  return baseTex.Sample(baseTexSampler, input.uvl);
}
