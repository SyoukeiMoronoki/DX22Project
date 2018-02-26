struct appdata
{
  float4 vertex : POSITION;
  float2 uv : TEXCOORD0;
  float4 normal : NORMAL0;
};

struct v2f
{
  float2 uv : TEXCOORD0;
  float4 vertex : SV_POSITION;
  float4 color : COLOR0;
};

texture _MainTex;
sampler _MainTexSampler = sampler_state
{
  Texture = _MainTex;
  MipFilter = LINEAR;
  MinFilter = LINEAR;
  MagFilter = LINEAR;
};

float4x4 _WorldViewProj;
float4 _Diffuse;
float4 _Ambient;

bool _UseEar;

static const float GRID_WIDTH = 0.005f;

v2f vert(appdata v)
{
  v2f o;
  o.vertex = mul(v.vertex, _WorldViewProj);
  o.uv = v.uv;
  o.color = _Diffuse * _Ambient;
  return o;
}

float4 frag(v2f i) : SV_TARGET
{
  if (_UseEar)
  {
    float d = 1.0f / 8.0f;
    float dx = fmod(i.uv.x, d) - d * 0.5f;
    float dy = fmod(i.uv.y, d) - d * 0.5f;
    return abs(dx) < GRID_WIDTH || abs(dy) < GRID_WIDTH ? float4(1.0f, 1.0f, 1.0f, 1.0f) : float4(0.0f, 0.0f, 0.0f, 0.0f);
  }
  return i.color;
}

technique Default
{
  pass
  {
    AlphaBlendEnable = TRUE;
    BlendOp = ADD;
    SrcBlend = SRCALPHA;
    DestBlend = INVSRCALPHA;
    ShadeMode = FLAT;
    ZEnable = TRUE;
    vertexshader = compile vs_2_0 vert();
    pixelshader = compile ps_2_0 frag();
  }
}
