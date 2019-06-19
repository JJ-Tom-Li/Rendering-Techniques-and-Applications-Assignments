# Final Project -- SnowCraft打雪仗
## 遊戲說明 
1. 如何開始遊戲?</br> 
    <pre>點擊Debug/final.exe即可開始遊戲</pre>
2. 如何操作? </br>
    <pre>開始選單:
    
      方向鍵左右選擇，Enter確認
      
    遊戲畫面:
    
      滑鼠移動腳色
      
      數字鍵1,2,3切換腳色
      
      滑鼠左鍵射擊(按住集氣，放開即可射擊)</pre> 
3. 如何離開遊戲? 
    <pre>Esc鍵可離開。</pre>
4. 如何開啟作弊模式? 
	  <pre>在開始畫面輸入:上上下下左右左右BA 可開啟作弊模式。</pre> 
## Directory tree
<pre>
|--final
|--include
|	|--GL	//opengl functions.
|	|--snowcraft
|	|	|--constants
|	|	|	|--init_constants.h		//存放各種常數與global variables，並include所有需要的headers，load model與建立Display list的function也在這裡。
|	|	|	|--vec.cpp				//自己寫的3D向量(座標)物件，可進行向量的加、減、dot與cross運算。
|	|	|--objects
|	|	|	|--bounding_box.cpp		//可用於碰撞偵測的bounding_box，這程式沒用到。
|	|	|	|--enemy.cpp			//定義Enemy物件。
|	|	|	|--hero.cpp				//定義Hero物件。
|	|	|	|--Moving_object.h		//各種移動物件的父類別，定義一個三維空間可移動的物件。
|	|	|	|--snowball.cpp			//定義Snowball物件。
|	|	|--scene
|	|	|	|--battle_scene.cpp		//定義戰場場景的物件。
|	|	|	|--death_scene.cpp		//定義死亡畫面的物件。
|	|	|	|--middle_scene.cpp		//定義過場畫面的物件。
|	|	|	|--pause_scene.cpp		//原定暫停畫面的物件宣告，並無實作。
|	|	|	|--scene.h				//各種場景物件的父類別，其中包含了滑鼠位置to3D座標的function，以及讀取texture的function。
|	|	|	|--start_menu.cpp		//定義開始畫面的物件。
|	|	|	|--win_scene.cpp		//定義勝利畫面的物件。
|	|	|--snowcraft.cpp	//定義整個遊戲的物件。
|--lib	//存放需要的lib
|--model
|   |--Lego		//樂高人model，己方操作人物
|   |--Snowman	//雪人怪物model，敵方人物
|--picture	//存放所有的texture
|--stage	//存放關卡設定資料
|--music	//存放音樂
|--final.cpp//主程式位置
|--glm.cpp	//obj model loader
</pre> 
## Informations
程式作者: NCHU 資工四 李家駿,柯冠名 </br>
Please contact us(email:tom86311@gmail.com) if you have any question. </br>
