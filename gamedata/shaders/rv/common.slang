module common;

public struct SceneData {
    public float4x4 m_WVP;
    public float4x4 m_WV;
    public float4x4 m_W;
    public float4 ambientColor;
    public float4 sunlightDirection;
    public float4 sunlightColor;


    public float4x4 m_V;
    public float4x4 m_inv_V;
    public float4x4 m_P;
    public float4x4 m_VP;

    public uint32_t frameNumber;
    public float deltaTime;
};

public struct Vertex {
    public float3 position;
    public float uv_x;
    public float3 normal;
    public float uv_y;
    public float4 color;
};

public struct BasePushConstantData {
    public Vertex *vertices;
    public uint32_t vertexIndex;
};

// Bindings 
[[vk::binding(0, 0)]]
public ConstantBuffer<SceneData> sceneData;