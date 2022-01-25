declare function doFile(path: string): string | number;
declare function doFileFunction(
    path: string,
    funName: string,
    retType: "string" | "none" | "number",
    ...args: Array<number | string>): string | number | void;
