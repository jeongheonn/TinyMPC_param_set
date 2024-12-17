This code is based on the following Git repository: https://github.com/TinyMPC/TinyMPC.


Window에서는 cmake 오류나서, wsl 환경에서 진행해야 함. 



<TinyMPC PreComputation Parameter 뽑는 코드> 

Precomputation parameter MATLAB과 교차 검증 완료하였음. 



    cd TinyMPC_param_set 
    
    mkdir build 
    
    cd build

    cmake ..

    cmake --build . 

    ./examples/quadrotor_tracking 



matlab dlqr 쓰면 안됨. 그것은 rho 고려 안함
