package main

import (
	"fmt"
	"io/ioutil"
	"strings"
)

func main() {
	defer fmt.Println("exit!!!")
//	fmt.Println(maps["CTRL"]) 
	var i int=6
	var op string
	var tmp string
	for(i!=7){
		fmt.Println("选择你要做什么：")
		fmt.Println("already:\n"+op)
		fmt.Println("1.准备按键  2.准备控制键  3.按下所准备的所有按键 4.按下某一个按键 5.按下某一个控制键  6.等20ms并松开所有按键 7.退出:")
		fmt.Scan(&i)
		if i==1{
			fmt.Println("准备那个按键:")
			fmt.Scan(&tmp)
			op=op+"	prepare_key(" +strings.ToUpper("kb_"+tmp)+ ");\n"
		}
		if i==2{
			fmt.Println("准备那个按键:")
			fmt.Scan(&tmp)
			op=op+"	prepare_ctl(" +strings.ToUpper("kb_"+tmp)+ ");\n"
		}
		if i==3{
			op=op+"	press_all();"+ "\n"
		}
		if i==4{
			fmt.Println("按那个按键:")
			fmt.Scan(&tmp)
			op=op+"	press_key(" +strings.ToUpper("kb_"+tmp)+ ");\n"
		}
		if i==5{
			fmt.Println("按那个控制键:")
			fmt.Scan(&tmp)
			op=op+"	press_ctl(" +strings.ToUpper("kb_"+tmp)+ ");\n"
		}
		if i==6{
			op=op+"	free_all_and_wait();\n"
		}
		if i==7{
			break
		}
		i=6
		tmp=""
		fmt.Println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n")
	}
	if i==7{
		template_file,_:=ioutil.ReadFile("template.c")
		ioutil.WriteFile("output.c", []byte(string(template_file)+op+"	while(1);\n}"), 0666)
		fmt.Println("生成完毕！")
	}
}
