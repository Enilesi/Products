import Link from "next/link";

const Notfound = () => {
    return (
        <>
            <div>Not found</div>
            <p>Sorry, the page you are looking for does not exist.</p>
            <Link href="/">Return Home</Link>
        </>
    );
};

export default Notfound;
