function Light_Canvas.RegisterType(index,type)
    print('type:',type,'index:',index);
    Light_Canvas.__types_arr[type] = index;
end


function Light_Canvas.CreateNode(type,name,parent)
    print('type:',type,'name:',name,'index:',Light_Canvas.__types_arr[type]);
    return LCCP_CreateNode(Light_Canvas.__types_arr[type],name)
end