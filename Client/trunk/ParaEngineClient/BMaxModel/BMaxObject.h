#pragma once
#include "MeshEntity.h"
#include "ParaXEntity.h"
#include "TileObject.h"
namespace ParaEngine
{
	class CParaXModel;
	class BMaxModel;
	struct SceneState;
	struct IParaPhysicsActor;
	class CPhysicsWorld;

	/* render with color and material. */
	class BMaxObject : public CTileObject
	{
	public:
		BMaxObject(void);
		virtual ~BMaxObject(void);

		ATTRIBUTE_DEFINE_CLASS(BMaxObject);
		ATTRIBUTE_SUPPORT_CREATE_FACTORY(BMaxObject);

		/** this class should be implemented if one wants to add new attribute. This function is always called internally.*/
		virtual int InstallFields(CAttributeClass* pClass, bool bOverride);

		virtual HRESULT Draw(SceneState * sceneState);

		void ApplyBlockLighting(SceneState * sceneState);

		virtual void GetLocalTransform(Matrix4* localTransform);
		virtual void UpdateGeometry();

		virtual AssetEntity* GetPrimaryAsset();
		virtual void SetAssetFileName(const std::string& sFilename);
		
		virtual Matrix4* GetAttachmentMatrix(Matrix4& pOut, int nAttachmentID = 0, int nRenderNumber = 0);

		/** set the scale of the object. This function takes effects on both character object and mesh object.
		* @param s: scaling applied to all axis.1.0 means original size. */
		virtual void SetScaling(float s);

		/** get the scaling. */
		virtual float GetScaling();


		virtual void LoadPhysics();
		virtual void UnloadPhysics();
		virtual void SetPhysicsGroup(int nGroup);
		virtual int GetPhysicsGroup();
		virtual void EnablePhysics(bool bEnable);
		virtual bool IsPhysicsEnabled();

		/** get the number of physics actors. If physics is not loaded, the returned value is 0. */
		int GetStaticActorCount();;
		
	private:
		/** size scale */
		float	m_fScale;
		AnimIndex m_CurrentAnim;
		ref_ptr<ParaXEntity>      m_pAnimatedMesh;

		/** all static physics actors in physics engine */ 
		vector<IParaPhysicsActor*> m_staticActors;

		// any bit wise combination of PHYSICS_METHOD
		DWORD m_dwPhysicsMethod;
		unsigned int m_nPhysicsGroup;

		/** a value between [0,1). last block light. */
		float m_fLastBlockLight;
		/** a hash to detect if the containing block position of this biped changed. */
		DWORD m_dwLastBlockHash;
	};
}