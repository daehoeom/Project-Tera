//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//
//  - Although many improvements were made to RenderMonkey FX  
//    file export, there are still situations that may cause   
//    compilation problems once the file is exported, such as  
//    occasional naming conflicts for methods, since FX format 
//    does not support any notions of name spaces. You need to 
//    try to create workspaces in such a way as to minimize    
//    potential naming conflicts on export.                    
//    
//  - Note that to minimize resulting name collisions in the FX 
//    file, RenderMonkey will mangle names for passes, shaders  
//    and function names as necessary to reduce name conflicts. 
//**************************************************************//

//--------------------------------------------------------------//
// Textured
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// DrawWater
//--------------------------------------------------------------//
string Textured_DrawWater_Disc : ModelData = ".\\Chap13-Shaders\\05-TextureTechnique\\[13-05]waterBase\\Disc.3ds";

float4x4 g_matWorld : World;
float4x4 g_matViewProjection : ViewProjection;


struct VS_INPUT 
{
   float4 Position : POSITION0;
   float3 Normal : NORMAL;
   float2 uv : TEXCOORD0;
};

struct VS_OUTPUT 
{
   float4 Position : POSITION0;
   float2 uv : TEXCOORD0;
};

VS_OUTPUT Textured_DrawWater_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Out;
   
   Out.Position = mul( Input.Position, g_matWorld );
   Out.Position = mul( Out.Position, g_matViewProjection );
   Out.uv = Input.uv;
   
   return( Out );   
}

texture diffuse_Tex
<
   string ResourceName = ".\\Chap13-Shaders\\05-TextureTechnique\\[13-05]waterBase\\Fieldstone.tga";
>;
sampler2D  diffuseMap = sampler_state
{
   Texture = (diffuse_Tex);
   MAGFILTER = LINEAR;
};
texture bump_Tex
<
   string ResourceName = ".\\Chap13-Shaders\\05-TextureTechnique\\[13-05]waterBase\\bumpnoisesemi64.tga";
>;
sampler2D  bumpMap = sampler_state
{
   Texture = (bump_Tex);
   MAGFILTER = LINEAR;
};
float      bumpiness = 0.01f;
float      fTime0_X : Time0_X;
float      flowspeed = 0.05f;

struct PS_INPUT 
{
   float2 uv : TEXCOORD0;
};

float4 Textured_DrawWater_Pixel_Shader_ps_main( PS_INPUT Input ) : COLOR0
{
   float2 uv = float2( Input.uv.x + fTime0_X * flowspeed, Input.uv.y );
   float3 normal;
   
   normal = tex2D(bumpMap, uv);
   
   float4 base = tex2D(diffuseMap, Input.uv.xy + bumpiness * normal.xy);
   
   float4 c = float4( base.rgb, 0.5 );
   return c;
   
}

//--------------------------------------------------------------//
// Technique Section for Textured
//--------------------------------------------------------------//
technique Textured
{
   pass DrawWater
   {
      CULLMODE = CCW;
      ALPHABLENDENABLE = TRUE;
      BLENDOP = ADD;
      DESTBLEND = INVSRCALPHA;
      SRCBLEND = SRCALPHA;

      VertexShader = compile vs_2_0 Textured_DrawWater_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 Textured_DrawWater_Pixel_Shader_ps_main();
   }

}

