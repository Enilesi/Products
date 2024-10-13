import Link from "next/link";
const Links = () => {
        const links =[
            {
                title:"Home",
                path:"/",
            },
            {
                title:"Products",
                path:"/products",
            },
            {
                title:"Categories",
                path:"/categories",
            },
            {
                title:"Contact",
                path:"/contact",
            },
            {
                title:"Cart",
                path:"/cart",
            },
            {
                title:"Login",
                path:"/login",
            }
        ]
        return (
        <div>
            {links.map((link=>(
                <Link href={link.path} key={link.title}>{link.title}</Link>
            )))}
        </div>
    
    )
}

export default Links